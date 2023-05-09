#include "FEMdataExchange.h"

#include "MainWindow/MainWindow.h"
#include "MeshData/meshKernal.h"
#include "MeshData/meshSet.h"
#include "MeshData/meshSingleton.h"
#include "MeshThreadBase.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <string>
#include <vtkCellType.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

namespace MeshData {
	FEMdataExchange::FEMdataExchange(const QString& filename, MeshOperation operation,
									 GUI::MainWindow* mw, int modelId)
		: m_fileName(filename)
		, m_operation(operation)
		, m_meshData(MeshData::getInstance())
		, MeshThreadBase(filename, operation, mw)
		, m_modelId(modelId)
	{
	}

	FEMdataExchange::~FEMdataExchange() {}

	bool FEMdataExchange::read()
	{
		QFile	file(m_fileName);
		int		a		 = m_fileName.lastIndexOf('/');
		int		b		 = m_fileName.lastIndexOf('.');
		int		nameSize = b - a - 1;
		QString fileName = m_fileName.mid(a + 1, nameSize);
		if(!file.exists())
			return false;

		if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return false;

		QTextStream in(&file);

		m_grid								= vtkUnstructuredGrid::New();
		vtkSmartPointer<vtkPoints> vtkPoint = vtkSmartPointer<vtkPoints>::New();

		while(!in.atEnd()) {
			QString		line	 = in.readLine();
			QStringList lineList = line.split(" ");
			lineList.removeAll(QString(""));
			if(lineList.isEmpty())
				continue;
			if(lineList[0] == "GRID") {
				appendNode(lineList, vtkPoint);
			} else if(lineList[0] == "CTRIA3") {
				appendElement(lineList);
			}
		}
		qDebug() << Num;
		qDebug() << fileName;
		m_grid->SetPoints(vtkPoint);
		MeshKernal* k = new MeshKernal;
		k->setName(fileName);
		k->setPath(m_fileName);
		k->setMeshData(m_grid);
		m_meshData->appendMeshKernal(k);
		return true;
	}
	bool FEMdataExchange::write()
	{
		return false;
	}
	void FEMdataExchange::run()
	{
		ModuleBase::ThreadTask::run();
		bool result = false;
		switch(m_operation) {
			case MESH_READ:
				emit showInformation(tr("Import FEM Mesh File From \"%1\"").arg(m_fileName));
				result = read();
				setReadResult(result);
				break;
			case MESH_WRITE:
				emit showInformation(tr("Export FEM Mesh File From \"%1\"").arg(m_fileName));
				result = write();
				setWriteResult(result);
				break;
		}
		defaultMeshFinished();
	}

	void FEMdataExchange::appendNode(QStringList lineList, vtkPoints* vtkPoint)
	{
		int	   lineSize = lineList.size();
		// qDebug() << lineList;
		double point[3];
		switch(lineSize) {
			case 3: {
				point[0] = lineList[2].mid(0, 8).toDouble();
				point[1] = lineList[2].mid(8, 8).toDouble();
				point[2] = lineList[2].mid(16).toDouble();
				break;
			}
			case 4: {
				if(lineList[2].size() > 8) {
					point[0] = lineList[2].mid(0, 8).toDouble();
					point[1] = lineList[2].mid(8).toDouble();
					point[2] = lineList[3].toDouble();
				} else {
					point[0] = lineList[2].toDouble();
					point[1] = lineList[3].mid(0, 8).toDouble();
					point[2] = lineList[3].mid(8).toDouble();
				}
				break;
			}
			case 5: {
				point[0] = lineList[2].toDouble();
				point[1] = lineList[3].toDouble();
				point[2] = lineList[4].toDouble();
				break;
			}
			default:
				return;
		}
		// qDebug() << pointId << " " << point[0] << " " << point[1] << " " << point[2];
		vtkPoint->InsertNextPoint(point);
		m_pointHash.insert(lineList[1].toInt(), m_pointId);
		m_pointId++;
	}

	void FEMdataExchange::appendElement(QStringList lineList)
	{
		if(lineList.size() < 6)
			return;

		VTKCellType				   cellType = VTK_EMPTY_CELL;
		vtkSmartPointer<vtkIdList> IdList	= vtkSmartPointer<vtkIdList>::New();

		elementTypeSelect(lineList[0], cellType);
		if(cellType == VTK_EMPTY_CELL)
			return;

		for(int i = 3; i < lineList.size(); i++) {
			int p = m_pointHash.value(lineList[i].toInt());
			IdList->InsertNextId(p);
		}
		m_grid->InsertNextCell(cellType, IdList);
	}
	void FEMdataExchange::elementTypeSelect(QString elementName, VTKCellType& type)
	{
		if(elementName == "CTRIA3") {
			type = VTK_TRIANGLE;
		} else if(elementName == "CTRIA6") {
			type = VTK_QUADRATIC_TRIANGLE;
		} else if(elementName == "CQUAD4") {
			type = VTK_QUAD;
		} else if(elementName == "CQUAD8") {
			type = VTK_QUADRATIC_QUAD;
		} else if(elementName == "CTETRA") {
			type = VTK_TETRA;
		} else if(elementName == "c") {
			type = VTK_QUADRATIC_TETRA;
		} else if(elementName == "CHEXA") {
			type = VTK_HEXAHEDRON;
		} else if(elementName == "cc") {
			type = VTK_QUADRATIC_HEXAHEDRON;
		}
	}
} // namespace MeshData