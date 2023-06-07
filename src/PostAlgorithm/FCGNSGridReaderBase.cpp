#include "FCGNSGridReaderBase.h"

#include "Common/DebugLogger.h"

#include <cgns_io.h>
#include <cgnslib.h>
#include <cgnstypes.h>
#include <vtkCellData.h>
#include <vtkDataSet.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStructuredGrid.h>

FCGNSGridReaderBase::FCGNSGridReaderBase(vtkMultiBlockDataSet* root)
	: _root(root)
{
}

void FCGNSGridReaderBase::setInfo(int fileIndex, int baseIndex, int zoneIndex)
{
	_fileIndex = fileIndex;
	_baseIndex = baseIndex;
	_zoneIndex = zoneIndex;
}

void FCGNSGridReaderBase::readCoordinate(int dim, int count, cgsize_t rangeMin[3],
										 cgsize_t rangeMax[3])
{
	_vertexList.clear();
	_vertexList.fill(VPoint(), count);

	// 坐标名称（CoordinateX，CoordinateY，CoordinateZ，CoordinateR，CoordinateTheta，CoordinatePhi等）
	// 参考http://cgns.github.io/CGNS_docs_current/sids/dataname.html#dataname_grid
	char coordinate_name[33] = { 0 };
	// 坐标值的数据类型（RealSingle 或者 RealDouble）
	CGNS_ENUMV(DataType_t) datatype;
	int result = 0;
	for(int i = 1; i <= dim; ++i) {
		// 读取坐标信息，构建数据存储数组
		result = cg_coord_info(_fileIndex, _baseIndex, _zoneIndex, i, &datatype, coordinate_name);
		if(CG_OK != result) {
			DebugError("Failed to get coordinate(index = %d) info\n", i);
			break;
		}
		void* xyz{ nullptr };
		if(datatype == CGNS_ENUMV(RealSingle)) {
			xyz = new float[count];
		} else if(datatype == CGNS_ENUMV(RealDouble)) {
			xyz = new double[count];
		} else {
			DebugError("Invalid data type for coordinate: %s\n", coordinate_name);
			break;
		}

		// 读取坐标数据
		// 官方文档（datatype不需要区分RealSingle或者RealDouble，可以自动处理，但是由于数据量一般比较大，考虑
		// 节约内存，也可以做区分）：The function cg_coord_read returns the coordinate array
		// coord_array, for the range prescribed by range_min and range_max. The array is returned
		// to the application in the data type requested in mem_datatype. This data type does not
		// need to be the same as the one in which the coordinates are stored in the file. A
		// coordinate array stored as double precision in the CGNS file can be returned to the
		// application as single precision, or vice versa. The functions cg_coord_general_read and
		// cg_coord_general_write allow for type conversion when both reading from and writing to
		// the file.
		result = cg_coord_read(_fileIndex, _baseIndex, _zoneIndex, coordinate_name, datatype,
							   rangeMin, rangeMax, xyz);
		if(CG_OK != result) {
			DebugError("Failed to read grid coordinate: %s\n", coordinate_name);
			break;
		}

		if(strcmp(coordinate_name, "CoordinateX") == 0) {
			if(datatype == CGNS_ENUMV(RealDouble)) {
				auto* c = static_cast<double*>(xyz);
				for(int ipt = 0; ipt < count; ++ipt)
					_vertexList[ipt].x = c[ipt];
			} else if(datatype == CGNS_ENUMV(RealSingle)) {
				auto* c = static_cast<float*>(xyz);
				for(int ipt = 0; ipt < count; ++ipt)
					_vertexList[ipt].x = c[ipt];
			}
		} else if(strcmp(coordinate_name, "CoordinateY") == 0) {
			if(datatype == CGNS_ENUMV(RealDouble)) {
				auto* c = static_cast<double*>(xyz);
				for(int ipt = 0; ipt < count; ++ipt)
					_vertexList[ipt].y = c[ipt];
			} else if(datatype == CGNS_ENUMV(RealSingle)) {
				auto* c = static_cast<float*>(xyz);
				for(int ipt = 0; ipt < count; ++ipt)
					_vertexList[ipt].y = c[ipt];
			}
		} else if(dim == 3 && (strcmp(coordinate_name, "CoordinateZ") == 0)) {
			if(datatype == CGNS_ENUMV(RealDouble)) {
				auto* c = static_cast<double*>(xyz);
				for(int ipt = 0; ipt < count; ++ipt)
					_vertexList[ipt].z = c[ipt];
			} else if(datatype == CGNS_ENUMV(RealSingle)) {
				auto* c = static_cast<float*>(xyz);
				for(int ipt = 0; ipt < count; ++ipt)
					_vertexList[ipt].z = c[ipt];
			}
			_dim = 3;
		}

		if(datatype == CGNS_ENUMV(RealSingle))
			delete[](float*)xyz;
		else if(datatype == CGNS_ENUMV(RealDouble))
			delete[](double*)xyz;
	}
}

void FCGNSGridReaderBase::readFlowSolution(vtkDataSet* grid)
{
	int result = 0;
	int nsol   = 0;
	result	   = cg_nsols(_fileIndex, _baseIndex, _zoneIndex, &nsol);
	if(CG_OK != result) {
		DebugError("Failed to read number of flow solution\n");
		return;
	} else {
		DebugInfo("Number of flow solution is %d\n", nsol);
	}

	_dataSet = grid;

	for(int isol = 1; isol <= nsol; ++isol) {
		CGNS_ENUMT(GridLocation_t) varloc;
		char sol_name[33] = { 0 };
		result = cg_sol_info(_fileIndex, _baseIndex, _zoneIndex, isol, sol_name, &varloc);
		if(CG_OK != result) {
			DebugError("Failed to read info of flow solution\n");
			return;
		} else {
			DebugInfo("Flow solution: %s, var location: %d\n", sol_name, varloc);
		}

		QList<QString> varNames;
		QList<void*>   values;
		QList<int>	   valueType; // 3-float 4-double

		readFieldData(isol, varloc, varNames, valueType, values);

		addValueToGrid(varloc, varNames, valueType, values);

		for(auto v : values)
			delete v;
		values.clear();
	}
}

void FCGNSGridReaderBase::readFieldData(int				solIndex, CGNS_ENUMT(GridLocation_t) loc,
										QList<QString>& varNames, QList<int>& valueType,
										QList<void*>& values)
{
	if(loc != CGNS_ENUMT(Vertex) && loc != CGNS_ENUMT(CellCenter))
	{
		DebugError("Unsupported grid location: %d\n", loc);
		return;
	}
	int OK		= 0;
	int nFields = 0;
	OK			= cg_nfields(_fileIndex, _baseIndex, _zoneIndex, solIndex, &nFields);
	if(CG_OK != OK) 
	{
		DebugError("Failed to read number of fields\n");
		return;
	}
	int valNum = 0;
	for(int iField = 1; iField <= nFields; ++iField) {
		CGNS_ENUMT(DataType_t)	datatype;
		char fieldName[33] = { 0 };
		OK = cg_field_info(_fileIndex, _baseIndex, _zoneIndex, solIndex, iField, &datatype,
						   fieldName);
		if(CG_OK != OK) {
			DebugError("Failed to read info of field[%d]\n", iField);
			return;
		} else
		{
			DebugInfo("Begin to parse field: %s\n", fieldName);
		}

		cgsize_t min[3] = { 1, 1, 1 }, max[3] = { 0 };
		if(!_isStructedGrid) {
			switch(loc) {
				case CGNS_ENUMT(Vertex):
					valNum = max[0] = max[1] = max[2] = _dataSet->GetNumberOfPoints();
					break;
				case CGNS_ENUMT(CellCenter):
					valNum = max[0] = max[1] = max[2] = _dataSet->GetNumberOfCells();
					break;
				default:
					break;
			}
		} else {
			auto sG = vtkStructuredGrid::SafeDownCast(_dataSet);
			int	 dims[3];
			sG->GetDimensions(dims);
			switch(loc) {
				case CGNS_ENUMT(Vertex):
					max[0] = dims[0];
					max[1] = dims[1];
					max[2] = dims[2];
					valNum = max[0] * max[1] * max[2];
					break;
				case CGNS_ENUMT(CellCenter):
					max[0] = dims[0] - 1;
					max[1] = dims[1] - 1;
					max[2] = dims[2] - 1;
					valNum = max[0] * max[1] * max[2];
					break;

				default:
					break;
			}
		}
		void* valuesArr = nullptr;

		if(datatype == CGNS_ENUMT(RealSingle))
			valuesArr = new float[valNum];
		else if(datatype == CGNS_ENUMT(RealDouble))
			valuesArr = new double[valNum];

		OK = cg_field_read(_fileIndex, _baseIndex, _zoneIndex, solIndex, fieldName, datatype, min,
						   max, valuesArr);
		if(CG_OK != OK) {
			DebugError("Failed to read flow solution for %s\n", fieldName);
			return;
		}

		varNames.append(fieldName);
		valueType.append(datatype);
		values.append(valuesArr);
	}
}

void FCGNSGridReaderBase::addValueToGrid(CGNS_ENUMT(GridLocation_t) loc, QList<QString> varNames,
										 QList<int> vType, QList<void*> valueList)
{
	QHash<QString, QHash<QString, QString>> vectorName;
	QStringList								scalarName;
	for(QString varName : varNames) {
		QString component, vecName;
		bool	isV = isVectorComponent(varName, vecName, component);
		if(isV) {
			vectorName[vecName].insert(component.toLower(), varName);
		} else
		{
			scalarName.append(varName);
		}
		
	}
	QStringList vecKeys = vectorName.keys();
	QStringList unVkeys;
	for(QString vecKey : vecKeys) {
		QHash<QString, QString> vvs = vectorName.value(vecKey);
		if(vvs.size() == _dim)
			continue;
		unVkeys.append(vecKey);
		scalarName.append(vvs.values());
	}
	for(QString uk : unVkeys)
		vectorName.remove(uk);

	if(CGNS_ENUMT(Vertex) == loc) {
		int	 nc			= _dataSet->GetNumberOfPoints();
		auto* pointArray = _dataSet->GetPointData();
		for(QString sca : scalarName) {
			int	  index = varNames.indexOf(sca);
			int	  type	= vType.at(index);
			void* v		= valueList.at(index);
			auto  array = generateScalarArray(sca, nc, type, v);
			pointArray->AddArray(array);
		}

		for(QString vec : vectorName.keys()) {
			QHash<QString, QString> comps = vectorName.value(vec);
			QString					comp  = comps.value("x");
			int						index = varNames.indexOf(comp);
			void*					x	  = valueList.at(index);
			int						xtype = vType.at(index);

			comp						  = comps.value("y");
			index						  = varNames.indexOf(comp);
			void* y						  = valueList.at(index);
			int	  ytype					  = vType.at(index);

			comp						  = comps.value("z");
			index						  = varNames.indexOf(comp);
			void* z						  = nullptr;
			int	  ztype					  = 0;
			if(index >= 0) {
				z	  = valueList.at(index);
				ztype = vType.at(index);
			}

			auto array = generateVectorArray(vec, nc, xtype, x, ytype, y, ztype, z);
			pointArray->AddArray(array);
		}
	} else if(CGNS_ENUMT(CellCenter) == loc) {
		int	 nc		   = _dataSet->GetNumberOfCells();
		auto cellArray = _dataSet->GetCellData();
		for(QString sca : scalarName) {
			int	  index = varNames.indexOf(sca);
			void* v		= valueList.at(index);
			int	  type	= vType.at(index);
			auto  array = generateScalarArray(sca, nc, type, v);
			cellArray->AddArray(array);
		}

		for(QString vec : vectorName.keys()) {
			QHash<QString, QString> comps = vectorName.value(vec);
			QString					comp  = comps.value("x");
			int						index = varNames.indexOf(comp);
			void*					x	  = valueList.at(index);
			int						xtype = vType.at(index);

			comp						  = comps.value("y");
			index						  = varNames.indexOf(comp);
			void* y						  = valueList.at(index);
			int	  ytype					  = vType.at(index);

			comp						  = comps.value("z");
			index						  = varNames.indexOf(comp);
			void* z						  = nullptr;
			int	  ztype					  = 0;
			if(index >= 0) {
				z	  = valueList.at(index);
				ztype = vType.at(index);
			}

			auto array = generateVectorArray(vec, nc, xtype, x, ytype, y, ztype, z);
			cellArray->AddArray(array);
		}
	}
}

bool FCGNSGridReaderBase::isVectorComponent(QString name, QString& vecName, QString& comp)
{
	QRegExp pattern("\\s*x$|\\s*X$|\\s*y$|\\s*Y$|\\s*z$|\\s*Z$");
	bool	is = false;
	is		   = name.contains(pattern);
	if(is) {
		comp	= name.right(1);
		vecName = name.remove(comp);
		if(vecName.isEmpty())
			return false;
	}
	return is;
}

vtkDataArray* FCGNSGridReaderBase::generateScalarArray(QString varName, int num, int type, void* va)
{
	vtkDataArray* array		  = nullptr;
	float*		  valueFloat  = nullptr;
	double*		  valueDouble = nullptr;

	if(type == 3) // float
	{
		array	   = vtkFloatArray::New();
		valueFloat = static_cast<float*>(va);
	} else if(type == 4) // double
	{
		array		= vtkDoubleArray::New();
		valueDouble = static_cast<double*>(va);
	}

	double v = 0;
	array->SetName(varName.toLatin1().data());
	for(int i = 0; i < num; ++i) {
		switch(type) {
			case 3:
				v = valueFloat[i];
				break;
			case 4:
				v = valueDouble[i];
				break;
			default:
				break;
		}
		array->InsertNextTuple1(v);
	}

	double range[2];
	array->GetRange(range);
	return array;
}

vtkDataArray* FCGNSGridReaderBase::generateVectorArray(QString varName, int num, int xType, void* x,
													   int yType, void* y, int zType, void* z)
{
	auto array = vtkDoubleArray::New();
	array->SetName(varName.toLatin1().data());
	array->SetNumberOfComponents(3);
	array->SetComponentName(0, "x");
	array->SetComponentName(1, "y");
	array->SetComponentName(2, "z");

	float * xFV = nullptr, *yFV = nullptr, *zFV = nullptr;
	double *xDV = nullptr, *yDV = nullptr, *zDV = nullptr;

	if(xType == 3) // float
		xFV = static_cast<float*>(x);
	else if(xType == 4) // double
		xDV = static_cast<double*>(x);

	if(yType == 3) // float
		yFV = static_cast<float*>(y);
	else if(yType == 4) // double
		yDV = static_cast<double*>(y);

	if(zType == 3) // float
		zFV = static_cast<float*>(z);
	else if(zType == 4) // double
		zDV = static_cast<double*>(z);

	double vx = 0, vy = 0, vz = 0;
	for(int i = 0; i < num; ++i) {
		switch(xType) {
			case 3:
				vx = xFV[i];
				break;
			case 4:
				vx = xDV[i];
				break;
			default:
				break;
		}

		switch(yType) {
			case 3:
				vy = yFV[i];
				break;
			case 4:
				vy = yDV[i];
				break;
			default:
				break;
		}

		switch(zType) {
			case 3:
				vz = zFV[i];
				break;
			case 4:
				vz = zDV[i];
				break;
			default:
				break;
		}

		array->InsertNextTuple3(vx, vy, vz);
	}
	return array;
}
