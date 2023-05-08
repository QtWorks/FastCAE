/**
 * @file ThreadTask.h
 * @brief 多线程任务基类头文件
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
#ifndef  THREADTASK_H
#define  THREADTASK_H

#include <QObject>
#include <QThread>
#include "moduleBaseAPI.h"

class QThread;

namespace GUI
{
	class MainWindow;
}

namespace ModuleBase{
	class ProcessBar;
	/**
	 * @brief 多线程任务基类
	 * @since 2.5.0
	 */
	class MODULEBASEAPI ThreadTask : public QObject
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		ThreadTask(GUI::MainWindow* m/*QString title*/);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ThreadTask();	

	signals:
		void start();
		void showProcessBar(QWidget*);
		void closeThread();
		void setFinishedStatus(int);
		void setRange(int, int);
		void showButton(bool);
		void showInformation(QString s);
		//void taskFinished(ThreadTask* t);

		/**
		 * @brief 任务线程结束时会触发该信号
		 * @since 2.5.0
		 */
		void threadFinished();
		void threadWait(int n);

	public slots:
		/**
		 * @brief 线程运行
		 * @since 2.5.0
		 */
		virtual void run() = 0;
		/**
		 * @brief 终止线程
		 * @since 2.5.0
		 */
		void stop();

	protected:
		///virtual void run() = 0;

		/**
		 * @brief 线程结束时调用该函数
		 * @since 2.5.0
		 */
		void threadTaskFinished();

	private:
		/**
		 * @brief 延时函数
		 * @param sec 延时时间（单位：s）
		 * @since 2.5.0
		 */
		void threadDelay(int sec);

	protected:
		/**
		 * @brief 进度条
		 * @since 2.5.0
		 */
		ProcessBar* _process;
		/**
		 * @brief 主窗口
		 * @since 2.5.0
		 */
		GUI::MainWindow* _mainwindow;
		/**
		 * @brief 线程任务标记位
		 * @since 2.5.0
		 */
		bool _threadRuning{ false };
		//QThread _thread;
		//QThread* _thread;
	};
}
#endif // THREADTASK_H

