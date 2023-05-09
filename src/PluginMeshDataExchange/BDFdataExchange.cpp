#include "BDFdataExchange.h"

#include "BCBase/BCUserDef.h"
#include "ConfigOptions/ConfigOptions.h"
#include "ConfigOptions/MaterialConfig.h"
#include "DataProperty/ParameterDouble.h"
#include "DataProperty/ParameterGroup.h"
#include "DataProperty/ParameterString.h"
#include "DataProperty/PropertyString.h"
#include "MainWindow/MainWindow.h"
#include "Material/Material.h"
#include "Material/MaterialFactory.h"
#include "Material/MaterialSingletion.h"
#include "MeshData/meshKernal.h"
#include "MeshData/meshSet.h"
#include "MeshData/meshSingleton.h"
#include "ModelData/modelDataBaseExtend.h"
#include "ModelData/modelDataSingleton.h"
#include "ModuleBase/ThreadTaskManager.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMap>
#include <QMessageBox>
#include <QPair>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>

namespace MeshData {

	const QMap<QString, QPair<int, VTKCellType>> allSupportElements = {
		std::map<QString, QPair<int, VTKCellType>>::value_type("CROD", qMakePair(2, VTK_LINE)),
		std::map<QString, QPair<int, VTKCellType>>::value_type("CBAR", qMakePair(2, VTK_LINE)),
		std::map<QString, QPair<int, VTKCellType>>::value_type("CQUAD4", qMakePair(4, VTK_QUAD)),
		std::map<QString, QPair<int, VTKCellType>>::value_type("CQUAD8",
															   qMakePair(8, VTK_QUADRATIC_QUAD)),
		std::map<QString, QPair<int, VTKCellType>>::value_type("CHEXA",
															   qMakePair(8, VTK_HEXAHEDRON)),
		std::map<QString, QPair<int, VTKCellType>>::value_type("CTETRA",
															   qMakePair(10, VTK_QUADRATIC_TETRA))

	};

	BDFDataExchange::BDFDataExchange(const QString& fileName, MeshOperation operation,
									 GUI::MainWindow* mw, int modelId)
		: MeshThreadBase(fileName, operation, mw)
		, _fileName(fileName)
		, _operation(operation)
		, _meshData(MeshData::getInstance())
		, _modelId(modelId)
		, _mw(mw)
	{
	}

	void BDFDataExchange::readLine(QString& line)
	{
		while(_threadRuning && !_stream->atEnd()) {
			// 此处不可删除空格，包括首末位置的空格
			line = _stream->readLine();
			if(line.startsWith("$"))
				continue;
			break;
		}
	}

	bool BDFDataExchange::readNodes(vtkUnstructuredGrid* g, QString& line, MeshKernal* k)
	{
		if(nullptr == g || nullptr == k) {
			return false;
		}
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		bool					   result = false;
		do {
			if(!_threadRuning)
				break;
			double point[3] = { 0 };
			int	   index	= 0;

			if(line.startsWith("GRID*")) {
				index	 = line.mid(8, 16).toInt();
				point[0] = line.mid(40, 16).toDouble();
				point[1] = line.mid(56, 16).toDouble();
				readLine(line);
				point[2] = line.mid(8, 16).toDouble();
			} else if(line.startsWith("GRID")) {
				index	 = line.mid(8, 16).toInt();
				point[0] = line.mid(24, 8).toDouble();
				point[1] = line.mid(32, 8).toDouble();
				point[2] = line.mid(40, 8).toDouble();
			} else {
				break;
			}
			// qDebug() << "Point : index=" << index << "; x=" << point[0] << "; y=" << point[1] <<
			// "; z=" << point[2] ; points->InsertPoint(index - 1, point);
			vtkIdType re = points->InsertNextPoint(point);
			_pointIndexMapping.insert(index, re);

			readLine(line);
			// node区域读取完毕
			if(!line.startsWith("GRID")) {
				break;
			}
		} while(_threadRuning && !_stream->atEnd());

		if(points->GetNumberOfPoints() > 2) {
			g->SetPoints(points);
			result = true;
		}
		return result;
	}

	bool BDFDataExchange::readElements(vtkUnstructuredGrid* g, MeshKernal* k)
	{
		if(nullptr == g || nullptr == k || _elementList.isEmpty()) {
			return false;
		}
		bool	result		 = true;
		int		cellPointNum = 1;

		QString cellType	 = "None";
		QString line		 = "";
		for(int i = 0; i < _elementList.size(); ++i) {
			line		 = _elementList.at(i);
			cellType	 = line.mid(0, 8).simplified();
			cellPointNum = allSupportElements.value(cellType).first;

			if(!_threadRuning) {
				result = false;
				break;
			}

			vtkSmartPointer<vtkIdList> indexList = vtkSmartPointer<vtkIdList>::New();

			int						   index	 = 3;
			QString					   s		 = line.mid(index * 8, 8);
			do {
				indexList->InsertNextId(_pointIndexMapping.value(s.toInt()));
				s = line.mid((++index) * 8, 8);
			} while(!s.isNull());

			// 是否为双行存储
			if(index == 9 && allSupportElements.value(cellType).first > 7) {
				line = _elementList.at(++i);
				for(int j = 1; j <= (allSupportElements.value(cellType).first - 6); ++j) {
					indexList->InsertNextId(_pointIndexMapping.value(line.mid(j * 8, 8).toInt()));
				}
			}

			g->InsertNextCell(allSupportElements.value(cellType).second, indexList);
		}

		return result;
	}

	bool BDFDataExchange::read()
	{
		QFileInfo info(_fileName);
		if(!info.exists())
			return false;
		QString name = info.fileName();
		QString path = info.filePath();
		QFile	file(_fileName);
		if(!file.open(QIODevice::ReadOnly))
			return false;
		_stream						 = new QTextStream(&file);
		vtkUnstructuredGrid* dataset = vtkUnstructuredGrid::New();
		MeshKernal*			 k		 = new MeshKernal;
		QString				 line;

		do {
			if(!_threadRuning) {
				file.close();
				return false;
			}
			this->readLine(line);
			if(line.startsWith("GRID") && (!readNodes(dataset, line, k))) {
				delete k;
				dataset->Delete();
				file.close();
				return false;
			} else {
				for(auto type : allSupportElements.keys()) {
					if(line.startsWith(type)) {
						_elementList.append(line);
						if(allSupportElements.value(type).first > 7) {
							readLine(line);
							_elementList.append(line);
						}
					}
				}
			}
			if(_modelId == -1)
				continue;

		} while(_threadRuning && !_stream->atEnd());

		// 保证先读取节点，再读取单元
		if(!readElements(dataset, k)) {
			delete k;
			dataset->Delete();
			file.close();
			return false;
		}

		if(dataset != nullptr) {
			k->setName(name);
			k->setPath(path);
			k->setMeshData((vtkDataSet*)dataset);
			_meshData->appendMeshKernal(k);
		}

		if(_modelId != -1) {
			emit _mw->updatePhysicsTreeSignal();
		}
		file.close();
		return true;
	}

	void BDFDataExchange::run()
	{
		ModuleBase::ThreadTask::run();
		bool result = false;
		switch(_operation) {
			case MESH_READ:
				emit showInformation(tr("Import BDF Mesh File From \"%1\"").arg(_fileName));
				result = read();
				setReadResult(result);
				break;
			case MESH_WRITE:
				emit showInformation(tr("This feature has not been implemented!"));
				break;
		}
		defaultMeshFinished();
	}

} // namespace MeshData
