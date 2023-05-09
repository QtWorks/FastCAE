#include "CDBdataExchange.h"

#include "MainWindow/MainWindow.h"
#include "MeshData/meshKernal.h"
#include "MeshData/meshSet.h"
#include "MeshData/meshSingleton.h"
#include "meshDataExchangePlugin.h"
#include "MeshThreadBase.h"

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QTextStream>
#include <vtkUnstructuredGrid.h>

namespace MeshData {
	CDBdataExchange::CDBdataExchange(const QString& filename, MeshOperation operation,
									 GUI::MainWindow* mw, int modelId)
		: m_filePath(filename)
		, m_operation(operation)
		, m_meshData(MeshData::getInstance())
		, MeshThreadBase(filename, operation, mw)
		, m_modelId(modelId)
	{
	}

	CDBdataExchange::~CDBdataExchange() {}

	void CDBdataExchange::run()
	{
		ModuleBase::ThreadTask::run();
		bool result = false;
		switch(m_operation) {
			case MESH_READ: {
				emit showInformation(tr("Import CDB Mesh File From \"%1\"").arg(m_filePath));
				result = read();
				setReadResult(result);
				break;
			}
			case MESH_WRITE: {
				emit showInformation(tr("Export CDB Mesh File From \"%1\"").arg(m_filePath));
				result = write();
				setWriteResult(result);
				break;
			}
		}
		defaultMeshFinished();
	}
	bool CDBdataExchange::read()
	{
		int		a		 = m_filePath.lastIndexOf('/');
		int		b		 = m_filePath.lastIndexOf('.');
		int		nameSize = b - a;
		QString fileName = m_filePath.mid(a, nameSize);
		QFile	file(m_filePath);

		if(!file.exists())
			return false;

		if(!file.open(QIODevice::ReadOnly))
			return false;

		m_grid = vtkUnstructuredGrid::New();
		QTextStream in(&file);
		int			AllNodeNum = -1;
		int			AllElemNum = -1;
		QString		LineType;
		vtkPoints*	points = vtkPoints::New();
		while(!in.atEnd()) {
			QString line = in.readLine();
			if(line.isEmpty())
				return false;
			QStringList lineList = line.split(" ");
			lineList.removeAll("");
			if(lineList.isEmpty())
				continue;
			if(lineList[0] == "NUMOFF,NODE,") {
				AllNodeNum = lineList[1].toInt();
				continue;
			}
			if(lineList[0] == "NUMOFF,ELEM,") {
				AllElemNum = lineList[1].toInt();
				continue;
			}
			if(AllNodeNum != -1 && AllElemNum != -1) {
				if(line.mid(0, 6) == "NBLOCK") {
					LineType = "NBLOCK";
					continue;
				} else if(line.mid(0, 6) == "EBLOCK") {
					LineType = "EBLOCK";
					continue;
				}

				if(LineType == "NBLOCK") {
					if(lineList.size() < 3)
						continue;
					readNode(line, lineList, points);
				} else if(LineType == "EBLOCK") {
					if(lineList.size() < 15)
						continue;
					readElement(lineList);
				}
			}
		}

		m_grid->SetPoints(points);
		MeshKernal* kernal = new MeshKernal;
		kernal->setName(fileName);
		kernal->setID(m_modelId);
		kernal->setMeshData(m_grid);
		m_meshData->appendMeshKernal(kernal);
		return true;
	}
	bool CDBdataExchange::write()
	{
		return false;
	}
	bool CDBdataExchange::readNode(QString line, QStringList lineList, vtkPoints* points)
	{
		double	point[3];
		QString p = line.mid(27);
		point[0]  = p.mid(0, 20).toDouble();
		point[1]  = p.mid(20, 20).toDouble();
		point[2]  = p.mid(40).toDouble();
		points->InsertNextPoint(point);
		m_pointHash.insert(lineList[0].toInt(), m_pointId);
		m_pointId++;
		return true;
	}
	bool CDBdataExchange::readElement(QStringList lineList)
	{
		VTKCellType				   cellType = VTK_TRIANGLE;
		vtkSmartPointer<vtkIdList> IdList	= vtkSmartPointer<vtkIdList>::New();
		int						   p		= m_pointHash.value(lineList[11].toInt());
		IdList->InsertNextId(p);
		p = m_pointHash.value(lineList[12].toInt());
		IdList->InsertNextId(p);
		p = m_pointHash.value(lineList[13].toInt());
		IdList->InsertNextId(p);

		m_grid->InsertNextCell(cellType, IdList);
		return true;
	}
} // namespace MeshData