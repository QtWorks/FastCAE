/**
 * @file GeometryThreadBase.cpp
 * @brief 几何文件交换类的线程基类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-18 15:35
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
#include "GeometryThreadBase.h"
#include "MainWindow/MainWindow.h"
#include "PythonModule/PyAgent.h"

namespace Geometry
{
	GeometryThreadBase::GeometryThreadBase(GUI::MainWindow *mw, QList<Geometry::GeometrySet *> &res) : ThreadTask(mw),
																									   _result(res)
	{
		connect(this, SIGNAL(showGeometryMessageSig(ModuleBase::Message)), _mainwindow, SIGNAL(printMessageToMessageWindow(ModuleBase::Message)));
		connect(this, SIGNAL(updateGeometryTree()), _mainwindow, SIGNAL(updateGeometryTreeSig()));
		connect(this, SIGNAL(updateActionsStates()), _mainwindow, SIGNAL(updateActionStatesSig()));
		connect(this, SIGNAL(updatePreGeometryActor()), _mainwindow, SIGNAL(updatePreGeometryActorSig()));
	}

	GeometryThreadBase::~GeometryThreadBase()
	{
	}

	void GeometryThreadBase::defaultGeometryFinished()
	{
		emit updateGeometryTree();
		//		emit updatePreGeometryActor();
		Py::PythonAgent::getInstance()->unLock();
		ModuleBase::ThreadTask::threadTaskFinished();
	}

	QList<GeometrySet *> &GeometryThreadBase::getResult()
	{
		return _result;
	}
}