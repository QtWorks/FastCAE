/**
 * @file RealTimeWindowBase.h
 * @brief 实时曲线绘制窗口
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 17:12
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
#ifndef REALTIMECURVES_H
#define REALTIMECURVES_H

#include "PostWidgetsAPI.h"
#include "ModuleBase/graphWindowBase.h"
#include "PostCustomPlot.h"
#include <QStringList>
#include <QList>
#include <QVector>
#include <QHash>

class QTextStream;

namespace Ui
{
	class RealTimeWindow;
}
namespace GUI
{
	class MainWindow;
}
namespace ModelData
{
	class ModelDataBaseExtend;
}

namespace Post
{
	//	class Post2DWindow;
	class RealTimeMonitor;
	class PostCustomPlot;

	/**
	 * @brief 实时曲线绘制窗口类
	 * @since 2.5.0
	 */
	class POSTAPI RealTimeWindowBase : public ModuleBase::GraphWindowBase
	{
		Q_OBJECT
	public:
		RealTimeWindowBase(GUI::MainWindow *mainwindow, int proID);
		~RealTimeWindowBase();
		///根据设置项自动填充监控文件
		//		void autoFillFiles();
		/**
		 * @brief 添加监控文件
		 * @param name 文件路径
		 * @since 2.5.0
		 */
		void appendFileName(QString name);
		/**
		 * @brief 设置刷新时间间隔 必须在startrefresh之前调用
		 * @param msc 刷新时间，单位为毫秒
		 * @since 2.5.0
		 */
		void setRefreshTime(int msc);
		/**
		 * @brief 开始刷新，文件变更即调用updateplot
		 * @since 2.5.0
		 */
		void startRefresh();
		//语言切换
		void reTranslate() override;
		//根据名称切换窗口
		void viewRealTimeWindow(QString name);

	private:
		void closeEvent(QCloseEvent *e) override;
		void readFile(QString f);
		QString readLine();
		void reDraw();
		QVector<double> getData(QString f, QString va);

	signals:
		void closeWindow(Post::RealTimeWindowBase *w);

	protected slots:
		virtual void updatePlot(QString fileName);
		void endMonitor(int proid);

	protected:
		Ui::RealTimeWindow *_ui{};
		QHash<QString, PostCustomPlot *> _widgetList;
		RealTimeMonitor *_monitor{};
		QStringList _fileNames{};
		QTextStream *_stream{};
		ModelData::ModelDataBaseExtend *_modelData{};

		QHash<QString, QHash<QString, QVector<double>>> _values;
	};
}

#endif
