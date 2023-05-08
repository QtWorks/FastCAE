/**
 * @file BREPdataExchange.cpp
 * @brief brep文件操作类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-24 10:21
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
#include "BREPdataExchange.h"
#include "Geometry/geometrySet.h"
#include "Geometry/geometryData.h"
#include <TopoDS_Shape.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <QFileInfo>
#include <QDebug>
#include "Common/Types.h"

namespace Geometry
{
	BREPdataExchange::BREPdataExchange(const QString &_fileName, GeometryOperation operation, GUI::MainWindow *mw, QList<GeometrySet *> &res, int KernalId) : GeometryThreadBase(mw, res),
																																							  _fileName(_fileName),
																																							  _operation(operation)
	{
		Q_UNUSED(KernalId)
	}

	BREPdataExchange::~BREPdataExchange()
	{
		// qDebug() << "Brep Delete!" << endl;
	}

	void BREPdataExchange::run()
	{
		ModuleBase::ThreadTask::run();
		switch (_operation)
		{
		case GEOMETRY_READ:
			emit showInformation(tr("Import Geometry File From \"%1\"").arg(_fileName));
			_isRead = readBrep();
			break;
		case GEOMETRY_WRITE:
			emit showInformation(tr("Export Geometry File From \"%1\"").arg(_fileName));
			_isWrite = writeBrep();
			break;
		}
		deriveGeometryTaskFinished();
	}

	bool BREPdataExchange::readBrep()
	{
		std::string str = _fileName.toStdString();
		const char *c_fn = str.c_str();
		TopoDS_Shape ashape;
		BRep_Builder builder;
		bool ok = BRepTools::Read(ashape, (const Standard_CString)c_fn, builder);
		if (!ok)
			return false;
		auto geoSet = new GeometrySet(IGES);

		TopTools_HSequenceOfShape *sequanceOfShape = new TopTools_HSequenceOfShape;
		sequanceOfShape->Append(ashape);

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

	bool BREPdataExchange::writeBrep()
	{
		TopoDS_Compound aRes;
		BRep_Builder aBuilder;
		aBuilder.MakeCompound(aRes);
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
			aBuilder.Add(aRes, *shape);
			success = true;
		}
		if (!success)
			return false;
		success = BRepTools::Write(aRes, _fileName.toStdString().c_str());
		return success;
	}

	void BREPdataExchange::deriveGeometryTaskFinished()
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
