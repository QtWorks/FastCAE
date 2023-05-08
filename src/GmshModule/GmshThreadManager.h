/**
 * @file GmshThreadManager.h
 * @brief 网格划分线程管理类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-04-01 10:53
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
#ifndef _GMESHMANAGER_H_
#define _GMESHMANAGER_H_

#include <QObject>
#include <QHash>
#include "GmshModuleAPI.h"

class QWidget;

namespace GUI
{
	class MainWindow;
}

namespace Gmsh
{
	class GmshThread;
	/**
	 * @brief 网格划分线程管理类
	 * @since 2.5.0
	 */
	class GMSHAPI GmshThreadManager : public QObject
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param mw 主窗口对象
		 * @since 2.5.0
		 */
		GmshThreadManager(GUI::MainWindow *mw);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GmshThreadManager() = default;
		/**
		 * @brief 增加新的线程
		 * @param w 窗口部件
		 * @param t 线程
		 * @since 2.5.0
		 */
		void insertThread(QWidget *w, GmshThread *t);
		/**
		 * @brief 停止所有线程
		 * @since 2.5.0
		 */
		void stopAll();
		/**
		 * @brief 是否有线程在运行
		 * @return bool
		 * @since 2.5.0
		 */
		bool isRuning();

	signals:
		/**
		 * @brief 增加新的线程并启动时会触发该信号
		 * @since 2.5.0
		 */
		void threadStarted(QWidget *);

	private slots:
		/**
		 * @brief 停止线程槽函数
		 * @param w
		 * @since 2.5.0
		 */
		void stopThread(QWidget *w);
		/**
		 * @brief 线程结束槽函数
		 * @param t
		 * @since 2.5.0
		 */
		void threadFinished(GmshThread *t);

	private:
		/**
		 * @brief 线程哈希表
		 * @since 2.5.0
		 */
		QHash<QWidget *, GmshThread *> _threadHash{};
	};
}

#endif