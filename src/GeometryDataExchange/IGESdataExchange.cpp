/**
 * @file IGESdataExchange.cpp
 * @brief iges文件操作类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-24 09:54
 * @copyright Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 *
 * ============================================================================
 * Program:   FastCAE
 *
 * Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 * See License or http://www.fastcae.com/ for details.
 *
 * BSD 3-Clause License
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.
 * ==================================================================================
 */
#include "IGESdataExchange.h"
#include "Geometry/geometryData.h"
#include "Geometry/geometrySet.h"
#include <QFileInfo>
#include <TopoDS_Shape.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Reader.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <IGESControl_Writer.hxx>
#include "Common/Types.h"
namespace Geometry
{
	IGESdataExchange::IGESdataExchange(const QString &fileName, GeometryOperation operation, GUI::MainWindow *mw, QList<GeometrySet *> &res, int KernalId) : GeometryThreadBase(mw, res),
																																							 _fileName(fileName),
																																							 _operation(operation)
	{
		Q_UNUSED(KernalId)
	}

	IGESdataExchange::~IGESdataExchange()
	{
	}

	void IGESdataExchange::run()
	{
		ModuleBase::ThreadTask::run();
		switch (_operation)
		{
		case GEOMETRY_READ:
			emit showInformation(tr("Import Geometry File From \"%1\"").arg(_fileName));
			_isRead = readIges();
			break;
		case GEOMETRY_WRITE:
			emit showInformation(tr("Export Geometry File From \"%1\"").arg(_fileName));
			_isWrite = writeIges();
			break;
		}
		deriveGeometryTaskFinished();
	}

	bool IGESdataExchange::readIges()
	{
		TopoDS_Shape aShape;
		IGESControl_Controller::Init();
		IGESControl_Reader Reader;
		std::string str = _fileName.toStdString();
		const char *c_fn = str.c_str();
		Standard_Integer status = Reader.ReadFile(c_fn);
		if (status != IFSelect_RetDone)
			return false;

		Reader.SetReadVisible(Standard_True);
		Reader.PrintCheckLoad(Standard_True, IFSelect_GeneralInfo);
		Reader.ClearShapes();
		Reader.TransferRoots();

		aShape = Reader.OneShape();
		auto geoSet = new GeometrySet(IGES);

		TopTools_HSequenceOfShape *sequanceOfShape = new TopTools_HSequenceOfShape;
		sequanceOfShape->Append(aShape);

		Standard_Integer index = sequanceOfShape->Length();
		TopoDS_Shape theCompSolid = sequanceOfShape->ChangeValue(index);
		TopoDS_Shape *shape = new TopoDS_Shape;
		*shape = theCompSolid;
		geoSet->setShape(shape);
		QFileInfo info(_fileName);
		const QString name = info.fileName();
		geoSet->setName(name);
		GeometryData::getInstance()->appendGeometrySet(geoSet);
		getResult().append(geoSet);
		return true;
	}

	bool IGESdataExchange::writeIges()
	{
		IGESControl_Controller::Init();
		IGESControl_Writer igesWriter;
		Geometry::GeometryData *data = Geometry::GeometryData::getInstance();

		const int nset = data->getGeometrySetCount();
		bool success = false;
		for (int i = 0; i < nset; ++i)
		{
			GeometrySet *set = data->getGeometrySetAt(i);
			if (set == nullptr)
				continue;
			TopoDS_Shape *shape = set->getShape();

			if (shape == nullptr)
				continue;
			igesWriter.AddShape(*shape);
			success = true;
		}
		if (!success)
			return false;

		igesWriter.ComputeModel();
		success = igesWriter.Write(_fileName.toStdString().c_str());
		return success;
	}

	void IGESdataExchange::deriveGeometryTaskFinished()
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
