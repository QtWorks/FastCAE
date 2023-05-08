/**
 * @file PlotTreeWidget.h
 * @brief 控制面板二维曲线绘制的树形菜单
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 14:22
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
#ifndef PLOTTREEWIDGET_H
#define PLOTTREEWIDGET_H

#include "PostPlotWidgetAPI.h"
#include <QTreeWidget>
#include <QMenu>
#include <QAction>

namespace GUI
{
	class MainWindow;
}

namespace PostPlot
{
	/**
	 * @brief 控制面板二维曲线绘制的树形菜单类
	 * @since 2.5.0
	 */
	class POSTPLOTWIDGETAPI PlotTreeWidget : public QTreeWidget
	{
		Q_OBJECT

	public:
		PlotTreeWidget(GUI::MainWindow *m, QWidget *parent = nullptr);
		~PlotTreeWidget();

	private:
		/**
		 * @brief 初始化树形菜单
		 * @since 2.5.0
		 */
		void init();
		/**
		 * @brief 右键菜单响应函数
		 * @since 2.5.0
		 */
		void contextMenuEvent(QContextMenuEvent *event) override;

	private slots:
		/**
		 * @brief 更新树形菜单
		 * @since 2.5.0
		 */
		void updatePlotTree();
		/**
		 * @brief 移除数据文件
		 * @param item 数据项item
		 * @since 2.5.0
		 */
		void deleteFile(QTreeWidgetItem *item);

	private:
		GUI::MainWindow *_mainWindow{};
		QTreeWidgetItem *_root{};
		QTreeWidgetItem *_currentItem{};
	};

}
#endif // PLOTTREEWIDGET_H
