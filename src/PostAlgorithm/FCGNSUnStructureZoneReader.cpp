#include "FCGNSUnStructureZoneReader.h"
#include <vtkMultiBlockDataSet.h>
#include <cgnstypes.h>
#include <cgns_io.h>
#include <cgnslib.h>
#include <QDebug>
#include <vtkUnstructuredGrid.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkDataSetWriter.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkIdTypeArray.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkInformation.h>
#include <vtkCellType.h>
#include "PostRenderData/Macros.hxx"

FCGNSUnStructeGridReader::FCGNSUnStructeGridReader(vtkMultiBlockDataSet *root)
	: FCGNSGridReaderBase(root)
{
	_isStructedGrid = false;
}

void FCGNSUnStructeGridReader::read()
{
	char zone_name[33] = {0};
	cgsize_t zoneSize[3] = {0, 0, 0};
	int OK = cg_zone_read(_fileIndex, _baseIndex, _zoneIndex, zone_name, zoneSize);
	if (CG_OK != OK)
		return;
	_zoneName = QString(zone_name);
	const int nVertex = zoneSize[0], nCell = zoneSize[1], nBoundary = zoneSize[2];

	int dim{0};
	OK = cg_ncoords(_fileIndex, _baseIndex, _zoneIndex, &dim);
	if (CG_OK != OK)
		return;

	//    vtkUnstructuredGrid* unsGrid = vtkUnstructuredGrid::New();

	DecCreVTKSmartPtr(vtkUnstructuredGrid, unsGrid)
		cgsize_t read_range[2][3] = {0};
	for (int ijk = 0; ijk < 3; ++ijk)
	{
		read_range[0][ijk] = 1;
		read_range[1][ijk] = nVertex;
	}

	this->readCoordinate(dim, nVertex, read_range[0], read_range[1]);

	DecCreVTKSmartPtr(vtkPoints, points) //形成整体点集合
		for (int i = 0; i < _vertexList.size(); ++i)
	{
		VPoint po = _vertexList.at(i);
		points->InsertNextPoint(po.x, po.y, po.z);
	}

	unsGrid->SetPoints(points);

	int nSection{0};
	cg_nsections(_fileIndex, _baseIndex, _zoneIndex, &nSection);

	QList<int> sectionList = sectionOrder(nSection);

	for (int iSection : sectionList)
	{
		char sectionName[33] = {0};
		cgsize_t istart = 0, iend = 0;
		int nbndry = 0, iparent_flag = 0;
		CGNS_ENUMT(ElementType_t)
		itype;
		OK = cg_section_read(_fileIndex, _baseIndex, _zoneIndex, iSection, sectionName, &itype, &istart, &iend, &nbndry, &iparent_flag);
		const int ncellCount = iend - istart + 1;

		qDebug() << QString(sectionName) << istart << iend;
		cgsize_t elementDataSize = 0;
		OK = cg_ElementDataSize(_fileIndex, _baseIndex, _zoneIndex, iSection, &elementDataSize);
		if (CG_OK != 0)
			continue;
		cgsize_t *elements = new cgsize_t[elementDataSize];
		OK = cg_elements_read(_fileIndex, _baseIndex, _zoneIndex, iSection, elements, NULL);
		if (CG_OK != 0)
			continue;
		FSection section(QString(sectionName), istart, iend); //记录section
		_sections.append(section);

		this->addCells(unsGrid, ncellCount, itype, elements);
	}
	this->readFlowSolution(unsGrid);
	this->spllitSection(unsGrid);
}

void FCGNSUnStructeGridReader::addCells(vtkUnstructuredGrid *grid, int ncell, CGNS_ENUMT(ElementType_t) type, cgsize_t *elements)
{
	if (CGNS_ENUMT(TRI_3) == type) //三角形
	{

		for (int iCnt = 0; iCnt < ncell; ++iCnt)
		{
			vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
			idlist->InsertNextId(elements[iCnt * 3 + 0] - 1);
			idlist->InsertNextId(elements[iCnt * 3 + 1] - 1);
			idlist->InsertNextId(elements[iCnt * 3 + 2] - 1);
			grid->InsertNextCell(VTK_TRIANGLE, idlist);
		}
	}
	else if (CGNS_ENUMT(BAR_2) == type) //二节点梁单元
	{
		for (int iCnt = 0; iCnt < ncell; ++iCnt)
		{
			vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
			idlist->InsertNextId(elements[iCnt * 2 + 0] - 1);
			idlist->InsertNextId(elements[iCnt * 2 + 1] - 1);
			grid->InsertNextCell(VTK_LINE, idlist);
		}
	}
	else if (CGNS_ENUMT(TETRA_4) == type) //四节点四面体
	{
		for (int iCnt = 0; iCnt < ncell; ++iCnt)
		{
			vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
			idlist->InsertNextId(elements[iCnt * 4 + 0] - 1);
			idlist->InsertNextId(elements[iCnt * 4 + 1] - 1);
			idlist->InsertNextId(elements[iCnt * 4 + 2] - 1);
			idlist->InsertNextId(elements[iCnt * 4 + 3] - 1);
			grid->InsertNextCell(VTK_TETRA, idlist);
		}
	}
	else if (CGNS_ENUMT(QUAD_4) == type) //四节点四边形
	{
		for (int iCnt = 0; iCnt < ncell; ++iCnt)
		{
			vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
			idlist->InsertNextId(elements[iCnt * 4 + 0] - 1);
			idlist->InsertNextId(elements[iCnt * 4 + 1] - 1);
			idlist->InsertNextId(elements[iCnt * 4 + 2] - 1);
			idlist->InsertNextId(elements[iCnt * 4 + 3] - 1);
			grid->InsertNextCell(VTK_QUAD, idlist);
		}
	}
	else if (CGNS_ENUMT(HEXA_8) == type) //八节点六面体
	{
		for (int iCnt = 0; iCnt < ncell; ++iCnt)
		{
			vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
			idlist->InsertNextId(elements[iCnt * 8 + 0] - 1);
			idlist->InsertNextId(elements[iCnt * 8 + 1] - 1);
			idlist->InsertNextId(elements[iCnt * 8 + 2] - 1);
			idlist->InsertNextId(elements[iCnt * 8 + 3] - 1);
			idlist->InsertNextId(elements[iCnt * 8 + 4] - 1);
			idlist->InsertNextId(elements[iCnt * 8 + 5] - 1);
			idlist->InsertNextId(elements[iCnt * 8 + 6] - 1);
			idlist->InsertNextId(elements[iCnt * 8 + 7] - 1);
			grid->InsertNextCell(VTK_HEXAHEDRON, idlist);
		}
	}
	else if (CGNS_ENUMT(PENTA_6) == type) //六节点三棱柱
	{
		for (int iCnt = 0; iCnt < ncell; ++iCnt)
		{
			vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
			idlist->InsertNextId(elements[iCnt * 6 + 0] - 1);
			idlist->InsertNextId(elements[iCnt * 6 + 1] - 1);
			idlist->InsertNextId(elements[iCnt * 6 + 2] - 1);
			idlist->InsertNextId(elements[iCnt * 6 + 3] - 1);
			idlist->InsertNextId(elements[iCnt * 6 + 4] - 1);
			idlist->InsertNextId(elements[iCnt * 6 + 5] - 1);
			grid->InsertNextCell(VTK_WEDGE, idlist);
		}
	}
	else if (CGNS_ENUMT(PYRA_5) == type) //金字塔单元
	{
		for (int iCnt = 0; iCnt < ncell; ++iCnt)
		{
			vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
			idlist->InsertNextId(elements[iCnt * 5 + 0] - 1);
			idlist->InsertNextId(elements[iCnt * 5 + 1] - 1);
			idlist->InsertNextId(elements[iCnt * 5 + 2] - 1);
			idlist->InsertNextId(elements[iCnt * 5 + 3] - 1);
			idlist->InsertNextId(elements[iCnt * 5 + 4] - 1);
			//            idlist->InsertNextId(elements[iCnt * 5 + 0] - 1);
			grid->InsertNextCell(VTK_PYRAMID, idlist);
		}
	}
}

void FCGNSUnStructeGridReader::spllitSection(vtkUnstructuredGrid *gird)
{
	if (_sections.isEmpty())
	{
		int n = _root->GetNumberOfBlocks();
		_root->SetBlock(n, gird);
		QString NameBC = _zoneName + "!|||!" + "None";
		_root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(), NameBC.toLatin1().data());
	}

	for (FSection sec : _sections)
	{
		//        vtkNew<vtkIdTypeArray> ids;
		DecCreVTKSmartPtr(vtkIdTypeArray, ids)
			ids->SetNumberOfComponents(1);
		for (int i = sec._begin - 1; i <= sec._end - 1; ++i)
			ids->InsertNextValue(i);

		//        vtkNew<vtkSelectionNode> node;
		DecCreVTKSmartPtr(vtkSelectionNode, node)
			node->SetFieldType(vtkSelectionNode::CELL);
		node->SetContentType(vtkSelectionNode::INDICES);
		node->SetSelectionList(ids);

		//        vtkNew<vtkSelection> section;
		DecCreVTKSmartPtr(vtkSelection, section);
		section->AddNode(node);

		//        vtkNew<vtkExtractSelection> exctra;
		DecCreVTKSmartPtr(vtkExtractSelection, exctra)
			exctra->SetInputData(0, gird);
		exctra->SetInputData(1, section);
		exctra->Update();

		auto secGrid = exctra->GetOutput();

		int n = _root->GetNumberOfBlocks();
		_root->SetBlock(n, secGrid);
		QString NameBC = sec._name + "!|||!" + "None";
		_root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(), NameBC.toLatin1().data());
		//       _root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(), sec._name.toLatin1().data());
	}
}

QList<int> FCGNSUnStructeGridReader::sectionOrder(int nsec)
{
	struct sectionInfo
	{
		sectionInfo(int index, int s)
		{
			Index = index;
			startNum = s;
		}
		int Index;
		int startNum;
	};
	auto compare = [](const sectionInfo &s1, const sectionInfo &s2) -> bool
	{
		return s1.startNum <= s2.startNum;
	};

	QList<sectionInfo> secs;
	for (int iSection = 1; iSection <= nsec; ++iSection)
	{
		char sectionName[33] = {0};
		cgsize_t istart = 0, iend = 0;
		int nbndry = 0, iparent_flag = 0;
		CGNS_ENUMT(ElementType_t)
		itype;
		int OK = cg_section_read(_fileIndex, _baseIndex, _zoneIndex, iSection, sectionName, &itype, &istart, &iend, &nbndry, &iparent_flag);
		if (OK != CG_OK)
			continue;
		sectionInfo sinfo(iSection, istart);
		secs.append(sinfo);
	}
	std::sort(secs.begin(), secs.end(), compare);

	QList<int> secOrders;
	for (auto s : secs)
	{
		secOrders.append(s.Index);
	}
	return secOrders;
}
