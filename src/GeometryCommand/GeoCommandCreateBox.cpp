/**
 * @file GeoCommandCreateBox.cpp
 * @brief 创建立方体（长方体）命令类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 17:07
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
#include "GeoCommandCreateBox.h"
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS.hxx>
#include "Geometry/geometryData.h"
#include "Geometry/geometrySet.h"
#include "Geometry/geometryParaBox.h"

namespace Command
{
	CommandCreateBox::CommandCreateBox(GUI::MainWindow *m, MainWidget::PreWindow *p)
		: GeoCommandBase(m, p)
	{
	}

	void CommandCreateBox::setName(QString name)
	{
		_name = name;
	}

	void CommandCreateBox::setLocation(double *loca)
	{
		_loaction[0] = loca[0];
		_loaction[1] = loca[1];
		_loaction[2] = loca[2];
	}

	void CommandCreateBox::setGeoPara(double *para)
	{
		_geoPara[0] = para[0];
		_geoPara[1] = para[1];
		_geoPara[2] = para[2];
	}

	bool CommandCreateBox::execute()
	{
		gp_Pnt pt(_loaction[0], _loaction[1], _loaction[2]);
		TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(pt, _geoPara[0], _geoPara[1], _geoPara[2]).Shape();
		TopoDS_Shape *shape = new TopoDS_Shape;
		*shape = aTopoBox;
		if (shape->IsNull())
		{
			delete shape;
			return false;
		}

		Geometry::GeometrySet *set = new Geometry::GeometrySet(Geometry::STEP);

		set->setShape(shape);
		_res = set;

		if (_isEdit)
		{
			set->setName(_editSet->getName());
			_geoData->replaceSet(set, _editSet);
			emit removeDisplayActor(_editSet);
		}
		else
		{
			set->setName(_name);
			_geoData->appendGeometrySet(set);
		}

		Geometry::GeometryParaBox *para = new Geometry::GeometryParaBox;
		para->setName(_name);
		para->setLocation(_loaction);
		para->setGeoPara(_geoPara);
		_res->setParameter(para);

		GeoCommandBase::execute();
		emit updateGeoTree();
		emit showSet(set);
		return true;
	}

	void CommandCreateBox::undo()
	{
		emit removeDisplayActor(_res);
		if (_isEdit)
		{
			_geoData->replaceSet(_editSet, _res);
			emit showSet(_editSet);
		}
		else
		{
			_geoData->removeTopGeometrySet(_res);
		}
		GeoCommandBase::undo();
		emit updateGeoTree();
	}

	void CommandCreateBox::redo()
	{
		if (_isEdit)
		{
			_geoData->replaceSet(_res, _editSet);
			emit removeDisplayActor(_editSet);
		}
		else
			_geoData->appendGeometrySet(_res);

		emit updateGeoTree();
		emit showSet(_res);
	}

	void CommandCreateBox::releaseResult()
	{
		if (_res != nullptr)
			delete _res;
		_res = nullptr;
	}

}