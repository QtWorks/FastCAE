/**
 * @file GeoCommandBase.cpp
 * @brief 几何命令基类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 16:19
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
#include "GeoCommandBase.h"
#include "Geometry/geometryData.h"
#include "MainWindow/MainWindow.h"
#include "MainWidgets/preWindow.h"
#include "GeometryCommand/GeoCommandList.h"

namespace Command
{

	GeoCommandBase::GeoCommandBase(GUI::MainWindow *m, MainWidget::PreWindow *p) : _mainWindow(m), _preWindow(p)
	{
		_geoData = Geometry::GeometryData::getInstance();

		if (_mainWindow != nullptr)
		{
			connect(this, SIGNAL(updateGeoTree()), _mainWindow, SIGNAL(updateGeometryTreeSig()));
			connect(this, SIGNAL(updateActions()), _mainWindow, SIGNAL(updateActionStatesSig()));
			connect(this, SIGNAL(updatePropertySig(DataProperty::DataBase *)), _mainWindow, SIGNAL(updateProperty(DataProperty::DataBase *)));
		}
		if (_preWindow != nullptr)
		{
			connect(this, SIGNAL(showSet(Geometry::GeometrySet *, bool)), _preWindow, SIGNAL(showGeoSet(Geometry::GeometrySet *, bool)));
			connect(this, SIGNAL(showDatum(Geometry::GeometryDatum *)), _preWindow, SIGNAL(showDatum(Geometry::GeometryDatum *)));
			connect(this, SIGNAL(removeDisplayActor(Geometry::GeometrySet *)), _preWindow, SIGNAL(removeGemoActors(Geometry::GeometrySet *)));
			connect(this, SIGNAL(removeDisplayDatumActor(Geometry::GeometryDatum *)), _preWindow, SIGNAL(removeGeoDatumActors(Geometry::GeometryDatum *)));
		}

		_commandList = GeoComandList::getInstance();
	}

	void GeoCommandBase::undo()
	{
		emit updatePropertySig(nullptr);
	}

	void GeoCommandBase::redo()
	{
	}

	bool GeoCommandBase::execute()
	{
		_commandList->clearRedoCommands();
		_commandList->clearSketchRedoCommands();
		emit updateActions();
		return true;
	}

	void GeoCommandBase::releaseResult()
	{
	}

	Command::CommandType GeoCommandBase::getComamndType()
	{
		return _type;
	}

	TopoDS_Shape *GeoCommandBase::getResultShape()
	{
		return _resShape;
	}

	void GeoCommandBase::setEditData(Geometry::GeometrySet *set)
	{
		_isEdit = set != nullptr;
		_editSet = set;
	}

}