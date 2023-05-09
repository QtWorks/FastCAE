#include "STLdataExchange.h"
#include "Geometry/geometrySet.h"
#include "Geometry/geometryData.h"
#include <QFileInfo>
#include <vtkSTLReader.h>

namespace Geometry
{
	STLdataExchange::STLdataExchange(const QString & fileName, GeometryOperation operation,
		GUI::MainWindow * mw, QList<GeometrySet*>& res, int KernalId) :
		GeometryThreadBase(mw, res),
		_fileName(fileName),
		_operation(operation)

	{
		Q_UNUSED(KernalId);
	}

	STLdataExchange::~STLdataExchange()
	{
	}

	void STLdataExchange::run()
	{
		ModuleBase::ThreadTask::run();
		switch (_operation)
		{
		case GEOMETRY_READ:
			emit showInformation(tr("Import Geometry File From \"%1\"").arg(_fileName));
			_isRead = readSTL();
			break;
		case GEOMETRY_WRITE:
			emit showInformation(tr("Export Geometry File From \"%1\"").arg(_fileName));
//			_isWrite = writeBrep();
			break;
		}
		deriveGeometryTaskFinished();
	}

	bool STLdataExchange::readSTL()
	{
		std::string str = _fileName.toStdString();
		const char* c_fn = str.c_str();
		auto reader = vtkSTLReader::New();
		reader->SetFileName(c_fn);
		reader->Update();
		auto stlTris = reader->GetOutput();
		const int nt = stlTris->GetNumberOfCells();
		if (nt > 0)
		{
			auto geoSet = new GeometrySet(STL);
			vtkPolyData* p = vtkPolyData::New();
			p->DeepCopy(stlTris);
			geoSet->setPoly(p);
			QFileInfo info(_fileName);
			const QString name = info.fileName();
			geoSet->setName(name);
			GeometryData::getInstance()->appendGeometrySet(geoSet);
			getResult().append(geoSet);
		}
		reader->Delete();

		return nt > 0;
	}

	void STLdataExchange::deriveGeometryTaskFinished()
	{
		ModuleBase::Message msg;
		if (_operation == GEOMETRY_READ)
		{
			if (_isRead)
			{
				emit updateActionsStates();
				emit showInformation(QString("Successful Import Geometry From \"%1\"").arg(_fileName));
				msg.type = Common::Message::Normal;
				msg.message = QString("Successful Import Geometry From \"%1\"").arg(_fileName);
				auto result = getResult();

				for (auto set : result)
				{
					if (set != result.last())
						emit ShowSetSig(set, false);
					else
						emit ShowSetSig(set);
				}
			}
			else
			{
				emit showInformation(QString("Failed Import Geometry From \"%1\"").arg(_fileName));
				msg.type = Common::Message::Error;
				msg.message = QString("Failed Import Geometry From \"%1\"").arg(_fileName);
			}
		}
		else if (_operation == GEOMETRY_WRITE)
		{
			if (_isWrite)
			{
				emit showInformation(QString("Successful Export Geometry From \"%1\"").arg(_fileName));
			}
			else
			{
				emit showInformation(QString("Failed Export Geometry From \"%1\"").arg(_fileName));
				msg.type = Common::Message::Error;
				msg.message = QString("Failed Export Geometry From \"%1\"").arg(_fileName);
			}
		}
		emit showGeometryMessageSig(msg);
		defaultGeometryFinished();
	}

}

