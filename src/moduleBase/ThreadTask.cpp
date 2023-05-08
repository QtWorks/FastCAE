/**
 * @file ThreadTask.cpp
 * @brief 多线程任务基类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-18 10:14
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
#include "ThreadTask.h"
#include "processBar.h"
#include "MainWindow/MainWindow.h"
//#include "MainWindow/SubWindowManager.h"
#include "ThreadTaskManager.h"
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <QTime>

namespace ModuleBase
{
	ThreadTask::ThreadTask(GUI::MainWindow *m) : _mainwindow(m)
	{
		_process = new ProcessBar(_mainwindow, this);

		// this->moveToThread(&_thread);
		//_thread.start();
		// 		_thread = new QThread{};
		// 		this->moveToThread(_thread);
		// 		_thread->start();

		// 		ThreadTaskManager* tm = ThreadTaskManager::getInstance();
		// 		tm->appendToThreadTaskList(this);

		// connect(this, SIGNAL(taskFinished(ThreadTask*)), tm, SLOT(removeTask(ThreadTask*)));
		// connect(this, &ThreadTask::start, this, &ThreadTask::run);
		// connect(&_thread, &QThread::start, this, &ThreadTask::run);
		// connect(this, &ThreadTask::closeThread, &_thread, &QThread::quit,Qt::AutoConnection);
		connect(this, SIGNAL(showProcessBar(QWidget *)), _mainwindow, SIGNAL(addProcessBarSig(QWidget *)));
		// connect(_thread, &QThread::finished, _thread, &QThread::deleteLater);
		//	connect(_thread, &QThread::finished, _thread, &QObject::deleteLater);
		// connect(_thread, &QThread::finished, this, &QObject::deleteLater);

		// connect(tm, &ThreadTaskManager::stopThread, this, &ThreadTask::stop);

		emit showProcessBar(_process);
	}

	ThreadTask::~ThreadTask()
	{
		// 		_thread->quit();
		// 		_thread->wait();
		qDebug() << "task del" << endl;
	}

	void ThreadTask::stop()
	{
		_threadRuning = false;
		// 		emit taskFinished(this);
		// 		_thread->quit();
		// 		delete this;
	}

	void ThreadTask::threadTaskFinished()
	{
		emit setRange(0, 100);
		_process->setAutoClose(false);
		emit setFinishedStatus(100);

		QThread::sleep(5); //该线程sleep不堵塞主线程
		// threadDelay(2);
		// emit threadWait(5);		//堵塞主线程

		_process->setAutoClose(true);
		emit setFinishedStatus(100);

		emit threadFinished();
	}

	void ThreadTask::threadDelay(int sec)
	{
		QTime dieTime = QTime::currentTime().addSecs(sec);
		while (QTime::currentTime() < dieTime)
			QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}

	void ThreadTask::run()
	{
		_threadRuning = true;
	}

}
