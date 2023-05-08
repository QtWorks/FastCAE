/**
 * @file GmshDialogBase.cpp
 * @brief 网格划分对话框基类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-31 18:21
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
#include "GmshDialogBase.h"
#include "PythonModule/PyAgent.h"
#include "MainWindow/MainWindow.h"
#include "LocalField.h"
//#include "PhysicalsGroups.h"

namespace Gmsh
{
	GmshDialogBase::GmshDialogBase(GUI::MainWindow *m, MainWidget::PreWindow *pre)
		: GeoDialogBase(m, pre)
	{
		_pyAgent = Py::PythonAgent::getInstance();
		connect(this, SIGNAL(showDialog(QDialog *)), m, SIGNAL(showDialogSig(QDialog *)));
		connect(this, SIGNAL(highLightMeshKernal(MeshData::MeshKernal *)), m, SIGNAL(highLightKernelSig(MeshData::MeshKernal *)));
	}

	GmshDialogBase::~GmshDialogBase()
	{
		emit setSelectMode((int)ModuleBase::None);

		for (LocalDensity *l : _localDensities)
			delete l;
		_localDensities.clear();
	}

	QList<LocalDensity *> *GmshDialogBase::getLocalDesities()
	{
		return &_localDensities;
	}

	// 	QList<PhysicalsGroups*>* GmshDialogBase::getPhysicalsGroups()
	// 	{
	// 		return &_physicalsGroups;
	// 	}

	void GmshDialogBase::appendLocalDesities()
	{
		for (LocalDensity *f : _localDensities)
		{
			f->appendLocals(_pyAgent);
		}
	}

	// 	void GmshDialogBase::appendPhysicals()
	// 	{
	// 		for (PhysicalsGroups* p : _physicalsGroups)
	// 		{
	// 			p->appendPhysicals(_pyAgent);
	// 		}
	// 	}

}
