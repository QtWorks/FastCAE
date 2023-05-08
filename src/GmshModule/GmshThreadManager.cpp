/**
 * @file GmshThreadManager.cpp
 * @brief 网格划分线程管理类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-04-01 10:55
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
#include "GmshThreadManager.h"
#include "MainWindow/MainWindow.h"
#include "ModuleBase/processBar.h"
#include "GmshThread.h"

namespace Gmsh
{

	GmshThreadManager::GmshThreadManager(GUI::MainWindow *mw)
	{
		connect(mw, SIGNAL(stopSolve(QWidget *)), this, SLOT(stopThread(QWidget *)));
		connect(this, SIGNAL(threadStarted(QWidget *)), mw, SIGNAL(addProcessBarSig(QWidget *)));
	}
	void GmshThreadManager::stopThread(QWidget *w)
	{
		GmshThread *t = _threadHash.value(w);
		if (t == nullptr)
			return;
		_threadHash.remove(w);
		t->stop();
		//		delete t;
	}

	void GmshThreadManager::insertThread(QWidget *w, GmshThread *t)
	{

		_threadHash.insert(w, t);
		emit threadStarted(w);
		connect(t, SIGNAL(threadFinished(GmshThread *)), this, SLOT(threadFinished(GmshThread *)));
		t->run();
	}

	void GmshThreadManager::threadFinished(GmshThread *t)
	{
		QWidget *w = _threadHash.key(t);
		delete t;
		_threadHash.remove(w);
		ModuleBase::ProcessBar *bar = dynamic_cast<ModuleBase::ProcessBar *>(w);
		if (bar == nullptr)
			return;
		bar->setProcessRange(0, 100);
		bar->setProcess(100);
	}

	void GmshThreadManager::stopAll()
	{
		QList<GmshThread *> ts = _threadHash.values();
		for (auto t : ts)
		{
			t->stop();
			delete t;
		}
		_threadHash.clear();
	}

	bool GmshThreadManager::isRuning()
	{
		return !_threadHash.isEmpty();
	}

}