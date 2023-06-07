#include "FCGNSUnStructureZoneReader.h"

#include "Common/DebugLogger.h"
#include "PostRenderData/Macros.hxx"

#include <cgns_io.h>
#include <cgnslib.h>
#include <cgnstypes.h>
#include <QDebug>
#include <vtkCellType.h>
#include <vtkDataSetWriter.h>
#include <vtkExtractSelection.h>
#include <vtkIdTypeArray.h>
#include <vtkInformation.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkUnstructuredGrid.h>

FCGNSUnStructeGridReader::FCGNSUnStructeGridReader(vtkMultiBlockDataSet* root)
	: FCGNSGridReaderBase(root)
{
	_isStructedGrid = false;
}

void FCGNSUnStructeGridReader::read()
{
	if(_fileIndex < 0 || _baseIndex < 0 || _zoneIndex < 0) {
		DebugError("Invalid zone(file: %d, base: %d, zone: %d)\n", _fileIndex, _baseIndex,
				   _zoneIndex);
		return;
	}
	DebugInfo("Start reading zone(file: %d, base: %d, zone: %d)...\n", _fileIndex, _baseIndex,
			  _zoneIndex);
	// 读取zone信息
	char	 zone_name[33] = { 0 };
	// 在非结构化网格数据中zonesize的元素分别对应NVertex, NCell, NBoundVertex
	cgsize_t zoneSize[3]   = { 0, 0, 0 };
	auto	 result		   = cg_zone_read(_fileIndex, _baseIndex, _zoneIndex, zone_name, zoneSize);
	if(CG_OK != result) {
		DebugError("Failed to read zone(index = %d) information\n", _zoneIndex);
		return;
	} else {
		DebugInfo("NVertex = %d, NCell = %d, NBoundVertex = %d\n", zoneSize[0], zoneSize[1],
				  zoneSize[2]);
	}

	_zoneName		  = QString(zone_name);
	const int nVertex = zoneSize[0], nCell = zoneSize[1], nBoundary = zoneSize[2];

	// 坐标数组的个数
	int		  dim{ 0 };
	result = cg_ncoords(_fileIndex, _baseIndex, _zoneIndex, &dim);
	if(CG_OK != result) {
		DebugError("Failed to read number of coordinate arrays for zone %d\n", _zoneIndex);
		return;
	} else {
		DebugInfo("Number of coordinate arrays for zone %d is %d\n", _zoneIndex, dim);
	}

	// 需要读取全部数据，所以range=[1,nVertex]
	cgsize_t read_range[2][3] = { 0 };
	for(int ijk = 0; ijk < 3; ++ijk) {
		read_range[0][ijk] = 1;
		read_range[1][ijk] = nVertex;
	}

	// 读取坐标数据信息
	this->readCoordinate(dim, nVertex, read_range[0], read_range[1]);
	if(_vertexList.size() != nVertex) {
		DebugError("Failed to read coordinate arrays for zone %d\n", _zoneIndex);
		return;
	}

	// 准备vtk数据，并插入点
	DecCreVTKSmartPtr(vtkPoints, points);
	for(int i = 0; i < _vertexList.size(); ++i) {
		auto po = _vertexList.at(i);
		points->InsertNextPoint(po.x, po.y, po.z);
	}
	DecCreVTKSmartPtr(vtkUnstructuredGrid, unsGrid);
	unsGrid->SetPoints(points);

	// 获取网格单元的节点数量
	int nSection{ 0 };
	result = cg_nsections(_fileIndex, _baseIndex, _zoneIndex, &nSection);
	if(CG_OK != result) {
		DebugError("Failed to get number of element sections\n");
		return;
	} else {
		DebugInfo("Number of element sections is %d\n", nSection);
	}

	QList<int> sectionList = sectionOrder(nSection);
	if(sectionList.size() == 0) {
		DebugError("Failed to order sections\n");
		return;
	}

	for(int iSection : sectionList) {
		char	 sectionName[33] = { 0 };
		cgsize_t istart = 0, iend = 0;
		int		 nbndry = 0, iparent_flag = 0;
		CGNS_ENUMT(ElementType_t)
		itype;
		result = cg_section_read(_fileIndex, _baseIndex, _zoneIndex, iSection, sectionName, &itype,
								 &istart, &iend, &nbndry, &iparent_flag);

		if(CG_OK != result) {
			DebugError("Failed to read element section: %d\n", iSection);
			return;
		} else {
			DebugInfo("element section: %s, element type: %d, first element index: %d, last "
					  "element index: %d\n",
					  sectionName, static_cast<int>(itype), istart, iend);
		}

		const int ncellCount	  = iend - istart + 1;
		cgsize_t  elementDataSize = 0;
		result = cg_ElementDataSize(_fileIndex, _baseIndex, _zoneIndex, iSection, &elementDataSize);
		if(CG_OK != result) {
			DebugError("Failed to get size of element connectivity data array\n");
			return;
		}
		cgsize_t* elements		= new cgsize_t[elementDataSize];
		cgsize_t* connectOffset = nullptr;
		/** */

		if(itype == CGNS_ENUMT(MIXED)) {
			connectOffset = new cgsize_t[elementDataSize];
			result = cg_poly_elements_read(_fileIndex, _baseIndex, _zoneIndex, iSection, elements,
										   connectOffset, NULL);
		} else {
			// 只能读取固定大小的单元类型
			result = cg_elements_read(_fileIndex, _baseIndex, _zoneIndex, iSection, elements, NULL);
		}
		if(CG_OK != result) {
			DebugError("Failed to read fixed size element data, error: %s\n", cg_get_error());
			return;
		}

		FSection section(QString(sectionName), istart, iend);
		_sections.append(section);

		this->addCells(unsGrid, ncellCount, itype, elements, connectOffset);
	}
	this->readFlowSolution(unsGrid);
	this->spllitSection(unsGrid);
}

/**
 * type：参考http://cgns.github.io/CGNS_docs_current/sids/conv.html#unstructgrid
 * ElementTypeNull, ElementTypeUserDefined, NODE, BAR_2, BAR_3, TRI_3, TRI_6, QUAD_4, QUAD_8,
 * QUAD_9, TETRA_4, TETRA_10, PYRA_5, PYRA_14, PENTA_6, PENTA_15, PENTA_18, HEXA_8, HEXA_20,
 * HEXA_27, MIXED, PYRA_13, NGON_n, NFACE_n, BAR_4, TRI_9, TRI_10, QUAD_12, QUAD_16, TETRA_16,
 * TETRA_20, PYRA_21, PYRA_29, PYRA_30, PENTA_24, PENTA_38, PENTA_40, HEXA_32, HEXA_56, HEXA_64,
 * BAR_5, TRI_12, TRI_15, QUAD_P4_16, QUAD_25, TETRA_22, TETRA_34, TETRA_35, PYRA_P4_29, PYRA_50,
 * PYRA_55, PENTA_33, PENTA_66, PENTA_75, HEXA_44, HEXA_98, HEXA_125
 *
 * CGNS的索引是从1开始的，VTK的索引是从0开始，需要注意
 */
void FCGNSUnStructeGridReader::addCells(vtkUnstructuredGrid* grid, int			  ncell,
										CGNS_ENUMT(ElementType_t) type, cgsize_t* elements,
										cgsize_t* connectOffset)
{
	if(CGNS_ENUMT(TRI_3) == type) // 三角形
	{
		for(int iCnt = 0; iCnt < ncell; ++iCnt) {
			addTri3Cell(grid, elements[iCnt * 3 + 0] - 1, elements[iCnt * 3 + 1] - 1,
						elements[iCnt * 3 + 2] - 1);
		}
	} else if(CGNS_ENUMT(BAR_2) == type) // 二节点梁单元
	{
		for(int iCnt = 0; iCnt < ncell; ++iCnt) {
			addBar2Cell(grid, elements[iCnt * 2 + 0] - 1, elements[iCnt * 2 + 1] - 1);
		}
	} else if(CGNS_ENUMT(TETRA_4) == type) // 四节点四面体
	{
		for(int iCnt = 0; iCnt < ncell; ++iCnt) {
			addTetra4Cell(grid, elements[iCnt * 4 + 0] - 1, elements[iCnt * 4 + 1] - 1,
						  elements[iCnt * 4 + 2] - 1, elements[iCnt * 4 + 3] - 1);
		}
	} else if(CGNS_ENUMT(QUAD_4) == type) // 四节点四边形
	{
		for(int iCnt = 0; iCnt < ncell; ++iCnt) {
			addQuad4Cell(grid, elements[iCnt * 4 + 0] - 1, elements[iCnt * 4 + 1] - 1,
						 elements[iCnt * 4 + 2] - 1, elements[iCnt * 4 + 3] - 1);
		}
	} else if(CGNS_ENUMT(HEXA_8) == type) // 八节点六面体
	{
		for(int iCnt = 0; iCnt < ncell; ++iCnt) {
			addHexa8Cell(grid, elements[iCnt * 8 + 0] - 1, elements[iCnt * 8 + 1] - 1,
						 elements[iCnt * 8 + 2] - 1, elements[iCnt * 8 + 3] - 1,
						 elements[iCnt * 8 + 4] - 1, elements[iCnt * 8 + 5] - 1,
						 elements[iCnt * 8 + 6] - 1, elements[iCnt * 8 + 7] - 1);
		}
	} else if(CGNS_ENUMT(PENTA_6) == type) // 六节点三棱柱
	{
		for(int iCnt = 0; iCnt < ncell; ++iCnt) {
			addPenta6Cell(grid, elements[iCnt * 6 + 0] - 1, elements[iCnt * 6 + 1] - 1,
						  elements[iCnt * 6 + 2] - 1, elements[iCnt * 6 + 3] - 1,
						  elements[iCnt * 6 + 4] - 1, elements[iCnt * 6 + 5] - 1);
		}
	} else if(CGNS_ENUMT(PYRA_5) == type) // 金字塔单元
	{
		for(int iCnt = 0; iCnt < ncell; ++iCnt) {
			addPyra5Cell(grid, elements[iCnt * 5 + 0] - 1, elements[iCnt * 5 + 1] - 1,
						 elements[iCnt * 5 + 2] - 1, elements[iCnt * 5 + 3] - 1,
						 elements[iCnt * 5 + 4] - 1);
		}
	} else if(CGNS_ENUMT(MIXED) == type && connectOffset != nullptr) { // 混合单元
		int iCnt = 0;
		int iEle = 0;
		while((iCnt < ncell) && (iEle == connectOffset[iCnt])) {
			// 混合单元比其他单元多存储一个值，即第一个值存储单元类型，后面是节点编号
			auto type = elements[iEle];
			switch(type) {
				case CGNS_ENUMT(BAR_2): {
					auto id1 = elements[++iEle] - 1;
					auto id2 = elements[++iEle] - 1;
					addBar2Cell(grid, id1, id2);
				} break;
				case CGNS_ENUMT(TRI_3): {
					auto id1 = elements[++iEle] - 1;
					auto id2 = elements[++iEle] - 1;
					auto id3 = elements[++iEle] - 1;
					addTri3Cell(grid, id1, id2, id3);
				} break;
				case CGNS_ENUMT(TETRA_4): {
					auto id1 = elements[++iEle] - 1;
					auto id2 = elements[++iEle] - 1;
					auto id3 = elements[++iEle] - 1;
					auto id4 = elements[++iEle] - 1;
					addTetra4Cell(grid, id1, id2, id3, id4);
				} break;
				case CGNS_ENUMT(QUAD_4): {
					auto id1 = elements[++iEle] - 1;
					auto id2 = elements[++iEle] - 1;
					auto id3 = elements[++iEle] - 1;
					auto id4 = elements[++iEle] - 1;
					addQuad4Cell(grid, id1, id2, id3, id4);
				} break;
				case CGNS_ENUMT(HEXA_8): {
					auto id1 = elements[++iEle] - 1;
					auto id2 = elements[++iEle] - 1;
					auto id3 = elements[++iEle] - 1;
					auto id4 = elements[++iEle] - 1;
					auto id5 = elements[++iEle] - 1;
					auto id6 = elements[++iEle] - 1;
					auto id7 = elements[++iEle] - 1;
					auto id8 = elements[++iEle] - 1;
					addHexa8Cell(grid, id1, id2, id3, id4, id5, id6, id7, id8);
				} break;
				case CGNS_ENUMT(PENTA_6): {
					auto id1 = elements[++iEle] - 1;
					auto id2 = elements[++iEle] - 1;
					auto id3 = elements[++iEle] - 1;
					auto id4 = elements[++iEle] - 1;
					auto id5 = elements[++iEle] - 1;
					auto id6 = elements[++iEle] - 1;
					addPenta6Cell(grid, id1, id2, id3, id4, id5, id6);
				} break;
				case CGNS_ENUMT(PYRA_5): {
					auto id1 = elements[++iEle] - 1;
					auto id2 = elements[++iEle] - 1;
					auto id3 = elements[++iEle] - 1;
					auto id4 = elements[++iEle] - 1;
					auto id5 = elements[++iEle] - 1;
					addPyra5Cell(grid, id1, id2, id3, id4, id5);
				} break;
				default:
					DebugError("Unsupported element type was found: %d\n", static_cast<int>(type));
					break;
			}
			++iEle;
			++iCnt;
		}
	} else {
		DebugError("Unsupported element type was found: %d\n", static_cast<int>(type));
	}
}

vtkIdType FCGNSUnStructeGridReader::addBar2Cell(vtkUnstructuredGrid* grid, vtkIdType id1,
												vtkIdType id2)
{
	auto idlist = vtkSmartPointer<vtkIdList>::New();
	idlist->InsertNextId(id1);
	idlist->InsertNextId(id2);
	return grid->InsertNextCell(VTK_LINE, idlist);
}

vtkIdType FCGNSUnStructeGridReader::addTri3Cell(vtkUnstructuredGrid* grid, vtkIdType id1,
												vtkIdType id2, vtkIdType id3)
{
	auto idlist = vtkSmartPointer<vtkIdList>::New();
	idlist->InsertNextId(id1);
	idlist->InsertNextId(id2);
	idlist->InsertNextId(id3);
	return grid->InsertNextCell(VTK_TRIANGLE, idlist);
}

vtkIdType FCGNSUnStructeGridReader::addTetra4Cell(vtkUnstructuredGrid* grid, vtkIdType id1,
												  vtkIdType id2, vtkIdType id3, vtkIdType id4)
{
	auto idlist = vtkSmartPointer<vtkIdList>::New();
	idlist->InsertNextId(id1);
	idlist->InsertNextId(id2);
	idlist->InsertNextId(id3);
	idlist->InsertNextId(id4);
	return grid->InsertNextCell(VTK_TETRA, idlist);
}

vtkIdType FCGNSUnStructeGridReader::addQuad4Cell(vtkUnstructuredGrid* grid, vtkIdType id1,
												 vtkIdType id2, vtkIdType id3, vtkIdType id4)
{
	auto idlist = vtkSmartPointer<vtkIdList>::New();
	idlist->InsertNextId(id1);
	idlist->InsertNextId(id2);
	idlist->InsertNextId(id3);
	idlist->InsertNextId(id4);
	return grid->InsertNextCell(VTK_QUAD, idlist);
}

vtkIdType FCGNSUnStructeGridReader::addHexa8Cell(vtkUnstructuredGrid* grid, vtkIdType id1,
												 vtkIdType id2, vtkIdType id3, vtkIdType id4,
												 vtkIdType id5, vtkIdType id6, vtkIdType id7,
												 vtkIdType id8)
{
	auto idlist = vtkSmartPointer<vtkIdList>::New();
	idlist->InsertNextId(id1);
	idlist->InsertNextId(id2);
	idlist->InsertNextId(id3);
	idlist->InsertNextId(id4);
	idlist->InsertNextId(id5);
	idlist->InsertNextId(id6);
	return grid->InsertNextCell(VTK_WEDGE, idlist);
}

vtkIdType FCGNSUnStructeGridReader::addPenta6Cell(vtkUnstructuredGrid* grid, vtkIdType id1,
												  vtkIdType id2, vtkIdType id3, vtkIdType id4,
												  vtkIdType id5, vtkIdType id6)
{
	auto idlist = vtkSmartPointer<vtkIdList>::New();
	idlist->InsertNextId(id1);
	idlist->InsertNextId(id2);
	idlist->InsertNextId(id3);
	idlist->InsertNextId(id4);
	idlist->InsertNextId(id5);
	idlist->InsertNextId(id6);
	return grid->InsertNextCell(VTK_WEDGE, idlist);
}

vtkIdType FCGNSUnStructeGridReader::addPyra5Cell(vtkUnstructuredGrid* grid, vtkIdType id1,
												 vtkIdType id2, vtkIdType id3, vtkIdType id4,
												 vtkIdType id5)
{
	auto idlist = vtkSmartPointer<vtkIdList>::New();
	idlist->InsertNextId(id1);
	idlist->InsertNextId(id2);
	idlist->InsertNextId(id3);
	idlist->InsertNextId(id4);
	idlist->InsertNextId(id5);
	return grid->InsertNextCell(VTK_PYRAMID, idlist);
}

void FCGNSUnStructeGridReader::spllitSection(vtkUnstructuredGrid* gird)
{
	if(_sections.isEmpty()) {
		int n = _root->GetNumberOfBlocks();
		_root->SetBlock(n, gird);
		QString NameBC = _zoneName + "!|||!" + "None";
		_root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(), NameBC.toLatin1().data());
	}

	for(FSection sec : _sections) {
		//        vtkNew<vtkIdTypeArray> ids;
		DecCreVTKSmartPtr(vtkIdTypeArray, ids) ids->SetNumberOfComponents(1);
		for(int i = sec._begin - 1; i <= sec._end - 1; ++i)
			ids->InsertNextValue(i);

		//        vtkNew<vtkSelectionNode> node;
		DecCreVTKSmartPtr(vtkSelectionNode, node) node->SetFieldType(vtkSelectionNode::CELL);
		node->SetContentType(vtkSelectionNode::INDICES);
		node->SetSelectionList(ids);

		//        vtkNew<vtkSelection> section;
		DecCreVTKSmartPtr(vtkSelection, section);
		section->AddNode(node);

		//        vtkNew<vtkExtractSelection> exctra;
		DecCreVTKSmartPtr(vtkExtractSelection, exctra) exctra->SetInputData(0, gird);
		exctra->SetInputData(1, section);
		exctra->Update();

		auto secGrid = exctra->GetOutput();

		int	 n		 = _root->GetNumberOfBlocks();
		_root->SetBlock(n, secGrid);
		QString NameBC = sec._name + "!|||!" + "None";
		_root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(), NameBC.toLatin1().data());
		//       _root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(),
		//       sec._name.toLatin1().data());
	}
}

QList<int> FCGNSUnStructeGridReader::sectionOrder(int nsec)
{
	struct sectionInfo {
		sectionInfo(int index, int s)
		{
			Index	 = index;
			startNum = s;
		}
		int Index;
		int startNum;
	};
	auto compare = [](const sectionInfo& s1, const sectionInfo& s2) -> bool {
		return s1.startNum <= s2.startNum;
	};

	QList<sectionInfo> secs;
	for(int iSection = 1; iSection <= nsec; ++iSection) {
		char	 sectionName[33] = { 0 };
		cgsize_t istart = 0, iend = 0;
		// 最后一个边界单元的索引，如果单元未排序则设为0
		int		 nbndry		  = 0;
		// 指示父级数据是否定义，如果存在则为1否则为0
		int		 iparent_flag = 0;
		CGNS_ENUMT(ElementType_t) itype;
		int result = cg_section_read(_fileIndex, _baseIndex, _zoneIndex, iSection, sectionName,
									 &itype, &istart, &iend, &nbndry, &iparent_flag);
		if(result != CG_OK) {
			DebugError("Failed to get info for an element section\n");
			return {};
		}
		sectionInfo sinfo(iSection, istart);
		secs.append(sinfo);
	}
	std::sort(secs.begin(), secs.end(), compare);

	QList<int> secOrders;
	for(auto s : secs) {
		secOrders.append(s.Index);
	}
	return secOrders;
}
