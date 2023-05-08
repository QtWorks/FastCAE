#include "KEYdataExchange.h"
#include "meshDataExchangePlugin.h"
#include "MeshData/meshSingleton.h"
#include "MeshData/meshKernal.h"
#include "MeshData/meshSet.h"
#include <QFile>
#include <QTextStream>
#include <vtkQuad.h>
#include <vtkHexahedron.h>
#include <vtkTetra.h>
#include <vtkQuadraticTetra.h>
#include <vtkQuadraticHexahedron.h>

namespace MeshData
{
	KEYdataExchange::KEYdataExchange(const QString &fileName, MeshOperation operation, GUI::MainWindow *mw, int modelId) : _meshData(MeshData::getInstance()),
																														   _operation(operation),
																														   _fileName(fileName),
																														   _stream(nullptr),
																														   MeshThreadBase(fileName, operation, mw),
																														   _modelId(modelId)
	{
	}

	KEYdataExchange::~KEYdataExchange()
	{
		if (_stream != nullptr)
		{
			delete _stream;
			_stream = nullptr;
		}
	}

	void KEYdataExchange::run()
	{
		ModuleBase::ThreadTask::run();
		bool result = false;
		switch (_operation)
		{
		case MESH_READ:
			emit showInformation(tr("Import KEY Mesh File From \"%1\"").arg(_fileName));
			result = read();
			setReadResult(result);
			break;
		case MESH_WRITE:
			emit showInformation(tr("Export KEY Mesh File From \"%1\"").arg(_fileName));
			result = write();
			setWriteResult(result);
			break;
		}
		defaultMeshFinished();
	}

	bool KEYdataExchange::read()
	{
		QFile file(_fileName);
		if (!file.open(QIODevice::ReadOnly))
			return false;
		_stream = new QTextStream(&file);

		QString aLine{};
		vtkSmartPointer<vtkUnstructuredGrid> grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		auto mk = new MeshKernal;
		mk->setMeshData(grid);
		const int mkID = mk->getID();
		while (!_stream->atEnd())
		{
			if (!_threadRuning)
				return false;
			readLine(aLine);
			if (aLine.startsWith("*NODE"))
				readNodes(grid, aLine);
			else if (aLine.startsWith("*ELEMENT_SOLID"))
				readElements(grid, aLine, mkID);
			else if (aLine.startsWith("*SET_NODE_LIST"))
				readNodesGroup(mkID, aLine);
		}
		if (grid->GetNumberOfPoints() < 1 || grid->GetNumberOfCells() < 1)
			return false;

		mk->setName(QString("KEY_%1").arg(mkID));
		mk->setPath(_fileName);
		mk->appendProperty("Points", (int)grid->GetNumberOfPoints());
		mk->appendProperty("Cells", (int)grid->GetNumberOfCells());
		_meshData->appendMeshKernal(mk);
		_meshData->generateDisplayDataSet();
		file.close();
		return true;
	}

	bool KEYdataExchange::readNodes(vtkSmartPointer<vtkUnstructuredGrid> grid, QString &aLine)
	{
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		while (!_stream->atEnd())
		{
			if (!_threadRuning)
				return false;
			readLine(aLine);
			if (aLine.startsWith("$"))
				break;
			if (aLine.size() < 56)
				continue;
			int nodeID = aLine.mid(0, 8).toInt();
			double nodeX = aLine.mid(8, 16).toDouble();
			double nodeY = aLine.mid(24, 16).toDouble();
			double nodeZ = aLine.mid(40, 16).toDouble();
			QStringList lineList = aLine.split(' ');
			points->InsertNextPoint(nodeX, nodeY, nodeZ);
		}
		grid->SetPoints(points);
		return true;
	}

	bool KEYdataExchange::readElements(vtkSmartPointer<vtkUnstructuredGrid> grid, QString &aLine, int mkId)
	{
		while (!_stream->atEnd())
		{
			if (!_threadRuning)
				return false;
			readLine(aLine);
			if (aLine.startsWith("$") || aLine.startsWith("*"))
				break;
			setGridCells(grid, aLine, mkId);
		}
		return true;
	}

	bool KEYdataExchange::readNodesGroup(const int mkID, QString &aLine)
	{
		MeshSet *ms = new MeshSet("", Node);
		if (ms == nullptr)
			return false;
		_meshData->appendMeshSet(ms);
		readLine(aLine);
		QStringList list = aLine.simplified().split(" ");
		int setID = list.at(0).toInt();
		ms->setName(QString("NodeSet_%1").arg(setID));
		ms->appendProperty("K_ID", setID);
		while (!_stream->atEnd())
		{
			if (!_threadRuning)
				return false;
			readLine(aLine);
			if (aLine.startsWith("*") || aLine.startsWith("$"))
				break;
			QStringList lineList = aLine.simplified().split(' ');
			for (QString str : lineList)
			{
				int cellIndex = str.toInt() - 1;
				ms->appendMember(mkID, cellIndex);
			}
		}
		return true;
	}

	void KEYdataExchange::setGridCells(vtkSmartPointer<vtkUnstructuredGrid> grid, QString &aLine, int mKid)
	{
		QMap<int, QVector<int>> cells{};
		while (!_stream->atEnd())
		{
			if (!_threadRuning)
				return;
			if (aLine.startsWith("$") || aLine.startsWith("*"))
				break;
			QStringList lineList = aLine.simplified().split(" ");
			int elementID = lineList.at(0).toInt();
			int cellID = lineList.at(1).toInt();
			cells[cellID].append(elementID - 1);
			int numOfPonits = lineList.size() - 2;
			switch (numOfPonits)
			{
			case 8:
			{
				vtkSmartPointer<vtkHexahedron> aHexahedronCell = vtkSmartPointer<vtkHexahedron>::New();
				aHexahedronCell->GetPointIds()->SetId(0, lineList.at(2).toInt() - 1);
				aHexahedronCell->GetPointIds()->SetId(1, lineList.at(3).toInt() - 1);
				aHexahedronCell->GetPointIds()->SetId(2, lineList.at(4).toInt() - 1);
				aHexahedronCell->GetPointIds()->SetId(3, lineList.at(5).toInt() - 1);
				aHexahedronCell->GetPointIds()->SetId(4, lineList.at(6).toInt() - 1);
				aHexahedronCell->GetPointIds()->SetId(5, lineList.at(7).toInt() - 1);
				aHexahedronCell->GetPointIds()->SetId(6, lineList.at(8).toInt() - 1);
				aHexahedronCell->GetPointIds()->SetId(7, lineList.at(9).toInt() - 1);
				grid->InsertNextCell(aHexahedronCell->GetCellType(), aHexahedronCell->GetPointIds());
			}
			break;
			case 4:
			{
				vtkSmartPointer<vtkTetra> aTetraCell = vtkSmartPointer<vtkTetra>::New();
				aTetraCell->GetPointIds()->SetId(0, lineList.at(2).toInt() - 1);
				aTetraCell->GetPointIds()->SetId(1, lineList.at(3).toInt() - 1);
				aTetraCell->GetPointIds()->SetId(2, lineList.at(4).toInt() - 1);
				aTetraCell->GetPointIds()->SetId(3, lineList.at(5).toInt() - 1);
				grid->InsertNextCell(aTetraCell->GetCellType(), aTetraCell->GetPointIds());
			}
			break;
			case 10:
			{
				vtkSmartPointer<vtkQuadraticTetra> aQTetraCell = vtkSmartPointer<vtkQuadraticTetra>::New();
				aQTetraCell->GetPointIds()->SetId(0, lineList.at(2).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(1, lineList.at(3).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(2, lineList.at(4).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(3, lineList.at(5).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(4, lineList.at(6).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(5, lineList.at(7).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(6, lineList.at(8).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(7, lineList.at(9).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(8, lineList.at(10).toInt() - 1);
				aQTetraCell->GetPointIds()->SetId(9, lineList.at(11).toInt() - 1);
				grid->InsertNextCell(aQTetraCell->GetCellType(), aQTetraCell->GetPointIds());
			}
			break;
			case 20:
			{
				vtkSmartPointer<vtkQuadraticHexahedron> aQHexCell = vtkSmartPointer<vtkQuadraticHexahedron>::New();
				aQHexCell->GetPointIds()->SetId(0, lineList.at(2).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(1, lineList.at(3).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(2, lineList.at(4).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(3, lineList.at(5).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(4, lineList.at(6).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(5, lineList.at(7).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(6, lineList.at(8).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(7, lineList.at(9).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(8, lineList.at(10).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(9, lineList.at(11).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(10, lineList.at(12).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(11, lineList.at(13).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(12, lineList.at(14).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(13, lineList.at(15).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(14, lineList.at(16).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(15, lineList.at(17).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(16, lineList.at(18).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(17, lineList.at(19).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(18, lineList.at(20).toInt() - 1);
				aQHexCell->GetPointIds()->SetId(19, lineList.at(21).toInt() - 1);
				grid->InsertNextCell(aQHexCell->GetCellType(), aQHexCell->GetPointIds());
			}
			break;
			default:
				break;
			}
			readLine(aLine);
		}
		QMapIterator<int, QVector<int>> it(cells);
		while (it.hasNext())
		{
			it.next();
			const int id = it.key();
			MeshSet *ms = new MeshSet("", Element);
			for (auto &id : it.value())
			{
				ms->appendMember(mKid, id);
			}
			_meshData->appendMeshSet(ms);

			ms->setName(QString("CellSet_%1").arg(id));
			ms->appendProperty("K_ID", id);
		}
	}

	void KEYdataExchange::readLine(QString &aLine)
	{
		while (_threadRuning)
		{
			if (_stream->atEnd())
			{
				//_threadRuning = false;
				break;
			}
			aLine = _stream->readLine();
			if (aLine.isEmpty())
				continue;
			break;
		}
	}

	bool KEYdataExchange::write()
	{
		// if (_modelId < 1)	return false;
		QFile file(_fileName);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
			return false;
		_stream = new QTextStream(&file);
		int a = _meshData->getKernalCount();

		auto mk = _meshData->getKernalByID(_modelId);
		//_meshData->
		auto grid = mk->getMeshData();
		// vtkUnstructuredGrid* grid = dynamic_cast<vtkUnstructuredGrid*>(mk->getMeshData());
		// writePointPart(grid);
		// writeCellPart(grid);
		writeMeshPart();
		file.close();
		return true;
	}

	bool KEYdataExchange::writePointPart(vtkDataSet *grid)
	{
		int index{0};
		int numOfPoint = grid->GetNumberOfPoints();
		*_stream << QString("   NODES   %1").arg(numOfPoint) << endl
				 << endl;
		while (index < numOfPoint)
		{
			if (!_threadRuning)
				return false;
			double *array = grid->GetPoint(index);
			index++;
			*_stream << QString("   %1   %2   %3   %4").arg(index).arg(array[0]).arg(array[1]).arg(array[2]) << endl;
		}
		return true;
	}

	bool KEYdataExchange::writeCellPart(vtkDataSet *grid)
	{
		int index{0}, hexahedronCount{0};
		int numOfCell = grid->GetNumberOfCells();
		*_stream << QString("   ELEMENTS   %1").arg(numOfCell) << endl
				 << endl;
		while (index < numOfCell)
		{
			if (!_threadRuning)
				return false;
			vtkCell *cell = grid->GetCell(index);
			if (cell == nullptr)
				continue;
			if (cell->GetCellType() == VTK_HEXAHEDRON)
			{
				hexahedronCount++;
				vtkIdList *PointIdIndexs = cell->GetPointIds();
				*_stream << QString("   %1   %2   %3   %4   %5   %6   %7   %8   %9").arg(hexahedronCount).arg(PointIdIndexs->GetId(0) + 1).arg(PointIdIndexs->GetId(1) + 1).arg(PointIdIndexs->GetId(2) + 1).arg(PointIdIndexs->GetId(3) + 1).arg(PointIdIndexs->GetId(4) + 1).arg(PointIdIndexs->GetId(5) + 1).arg(PointIdIndexs->GetId(6) + 1).arg(PointIdIndexs->GetId(7) + 1) << endl;
			}
			index++;
		}
		return false;
	}

	bool KEYdataExchange::writeMeshPart()
	{
		QList<int> setIds = _meshData->getSetIDFromKernal(_modelId);
		for (int setId : setIds)
		{
			auto ms = _meshData->getMeshSetByID(setId);
		}
		return false;
	}
}