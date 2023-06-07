#include "FCGNSStructureZoneReader.h"

#include "PostRenderData/Macros.hxx"

#include <cgns_io.h>
#include <cgnslib.h>
#include <cgnstypes.h>
#include <vtkDataSetWriter.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkInformation.h>
#include <vtkInformationStringKey.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>

FCGNSStructeGridReader::FCGNSStructeGridReader(vtkMultiBlockDataSet* root)
	: FCGNSGridReaderBase(root)
{
	_isStructedGrid = true;
}

void FCGNSStructeGridReader::read()
{
	char	 zone_name[33]	= { 0 };
	cgsize_t zoneSize[3][3] = { 0 };
	int		 OK = cg_zone_read(_fileIndex, _baseIndex, _zoneIndex, zone_name, zoneSize[0]);
	if(CG_OK != OK)
		return;
	_zoneName = QString(zone_name);

	int dim{ 0 };
	OK = cg_ncoords(_fileIndex, _baseIndex, _zoneIndex, &dim);
	if(CG_OK != OK)
		return;

	cgsize_t read_range[2][3] = { 0 };
	for(int ijk = 0; ijk < 3; ++ijk) {
		read_range[0][ijk] = 1;
		read_range[1][ijk] = zoneSize[0][ijk];
	}
	int nVertex = zoneSize[0][0] * zoneSize[0][1] * zoneSize[0][2];
	this->readCoordinate(dim, nVertex, read_range[0], read_range[1]);

	vtkStructuredGrid* sGrid = vtkStructuredGrid::New();
	sGrid->SetDimensions(zoneSize[0][0], zoneSize[0][1], zoneSize[0][2]);
	//   vtkNew<vtkPoints> points;                     //形成整体点集合
	DecCreVTKSmartPtr(vtkPoints, points)

		for(int i = 0; i < _vertexList.size(); ++i)
	{
		VPoint po = _vertexList.at(i);
		points->InsertNextPoint(po.x, po.y, po.z);
	}

	sGrid->SetPoints(points);

	this->readFlowSolution(sGrid);

	if(_readBC)
		this->readBC();

	this->spllitSection(sGrid);
}

void FCGNSStructeGridReader::setReadBC(bool r)
{
	_readBC = r;
}

bool FCGNSStructeGridReader::isReadBC()
{
	return _readBC;
}

void FCGNSStructeGridReader::readBC()
{
	int nbc{ 0 };
	int OK = cg_nbocos(_fileIndex, _baseIndex, _zoneIndex, &nbc);
	if(CG_OK != OK)
		return;
	for(int ibc = 1; ibc <= nbc; ++ibc) {
		CGNS_ENUMT(BCType_t) bctype;
		CGNS_ENUMT(PointSetType_t) ptype;
		// CGNS_ENUMT(GridLocation_t) location;
		CGNS_ENUMT(DataType_t) datatype;
		char	 bc_name[33]  = { 0 };
		int		 nrmlindex[3] = { 0 };
		cgsize_t np = 0, is = 0;
		int		 ib = 0;

		OK = cg_boco_info(_fileIndex, _baseIndex, _zoneIndex, ibc, bc_name, &bctype, &ptype, &np,
						  nrmlindex, &is, &datatype, &ib);
		if(CG_OK != OK)
			continue;
		if(ptype != CGNS_ENUMV(PointRange))
			continue;

		cgsize_t* pnpnts = new cgsize_t[6];
		OK				 = cg_boco_read(_fileIndex, _baseIndex, _zoneIndex, ibc, pnpnts, NULL);
		if(OK != CG_OK)
			continue;

		BCInfo info(bc_name, pnpnts, bctype);
		_bcList.append(info);
	}
}

void FCGNSStructeGridReader::spllitSection(vtkStructuredGrid* gird)
{
	int n = _root->GetNumberOfBlocks();
	_root->SetBlock(n, gird);
	QString NameBC = _zoneName + "!|||!" + "None";
	_root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(), NameBC.toLatin1().data());

	extractBCs(gird);
}

void FCGNSStructeGridReader::extractBCs(vtkStructuredGrid* grid)
{
	int dim[3] = { 0 };
	grid->GetDimensions(dim);
	for(BCInfo bc : _bcList) {
		QList<int> ptIndexs;
		for(int k = bc.kMin; k <= bc.kMax; ++k) {
			for(int j = bc.jMin; j <= bc.jMax; ++j) {
				for(int i = bc.iMin; i <= bc.iMax; ++i) {
					int index = dim[0] * dim[1] * k + dim[0] * j + i;
					ptIndexs.append(index);
				}
			}
		}
		extractBCGrid(grid, &bc, ptIndexs);
	}
}

void FCGNSStructeGridReader::extractBCGrid(vtkStructuredGrid* grid, BCInfo* info,
										   QList<int>& indexs)
{
	vtkStructuredGrid* bcMesh = vtkStructuredGrid::New();
	const int		   iDim	  = info->iMax - info->iMin + 1;
	const int		   jDim	  = info->jMax - info->jMin + 1;
	const int		   kDim	  = info->kMax - info->kMin + 1;

	bcMesh->SetDimensions(iDim, jDim, kDim);

	DecCreVTKSmartPtr(vtkPoints, points) for(int index : indexs)
	{
		double* coor = grid->GetPoint(index);
		points->InsertNextPoint(coor);
	}
	bcMesh->SetPoints(points);

	vtkPointData* pointData = grid->GetPointData();
	const int	  nArray	= pointData->GetNumberOfArrays();

	for(int iArray = 0; iArray < nArray; ++iArray) {
		const char*	  name		= pointData->GetArrayName(iArray);
		vtkDataArray* array		= pointData->GetArray(name);
		const int	  nComp		= array->GetNumberOfComponents();

		vtkDataArray* copyArray = nullptr;

		if(array->IsA("vtkDoubleArray"))
			copyArray = vtkDoubleArray::New();
		else if(array->IsA("vtkFloatArray"))
			copyArray = vtkFloatArray::New();
		if(copyArray == nullptr)
			continue;
		copyArray->SetName(name);

		copyArray->SetNumberOfComponents(nComp);
		for(int ic = 0; ic < nComp; ++ic) {
			const char* arrName = array->GetComponentName(ic);
			copyArray->SetComponentName(ic, arrName);
		}
		//       copyArray->Resize(indexs.size());
		for(int in = 0; in < indexs.size(); ++in) {
			int index = indexs.at(in);
			for(int ic = 0; ic < nComp; ++ic) {
				double v = array->GetComponent(index, ic);
				copyArray->InsertComponent(in, ic, v);
			}
		}
		bcMesh->GetPointData()->AddArray(copyArray);
	}

	int n = _root->GetNumberOfBlocks();
	_root->SetBlock(n, bcMesh);
	QString NameBC = info->name + "!|||!" + info->BCType;
	_root->GetMetaData(n)->Set(vtkCompositeDataSet::NAME(), NameBC.toLatin1().data());
}

QString GetBCType(QString name, int bcType)
{
	QString sBCType{ "None" };
	QString sName = name.toLower();
	if(bcType == 7) {
		sBCType = "Far";
		return sBCType;
	} else if(bcType >= 16 && bcType <= 17) {
		sBCType = "Sym";
		return sBCType;
	} else if(bcType >= 20 && bcType <= 24) {
		sBCType = "Wall";
		return sBCType;
	} else if(sName.contains("far")) {
		sBCType = "Far";
		return sBCType;
	} else if(sName.contains("sym")) {
		sBCType = "Sym";
		return sBCType;
	} else if(sName.contains("wall")) {
		sBCType = "Wall";
		return sBCType;
	}
	return sBCType;
}
