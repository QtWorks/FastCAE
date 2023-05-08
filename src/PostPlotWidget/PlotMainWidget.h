/**
 * @file PlotMainWidget.h
 * @brief 二维绘图plot主界面类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 13:51
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
#ifndef PLOTMAINWIDGET_H
#define PLOTMAINWIDGET_H

#include <QWidget>
#include "PostPlotWidgetAPI.h"
#include "PlotWidget.h"
#include "PropertyWidget.h"
#include <QMenu>
#include <QAction>

namespace Ui
{
	class PlotMainWidget;
}

namespace PostPlot
{
	/**
	 * @brief 二维绘图plot主界面类
	 * @since 2.5.0
	 */
	class POSTPLOTWIDGETAPI PlotMainWidget : public QWidget
	{
		Q_OBJECT

	public:
		PlotMainWidget(QWidget *parent = nullptr);
		~PlotMainWidget();

		/**
		 * @brief 初始化界面、菜单
		 * @since 2.5.0
		 */
		void init();
		/**
		 * @brief 读取曲线数据文件
		 * @param fileName 文件路径
		 * @since 2.5.0
		 */
		void readfile(QString fileName);
		/**
		 * @brief 添加曲线
		 * @param data_x 曲线的横坐标数组
		 * @param data_y 曲线的纵坐标数组
		 * @param curvename 曲线名称
		 * @since 2.5.0
		 */
		void post2DaddCurve(QVector<double> data_x, QVector<double> data_y, QString curvename);
		/**
		 * @brief 移除曲线
		 * @param curvename 曲线名称
		 * @since 2.5.0
		 */
		void post2DdelCurve(QString curvename);

	private slots:
		//添加曲线对话框
		void DataSetting();
		//标题设置对话框
		void TitleSetting();
		//坐标轴设置对话框
		void AxisSetting();
		//背景设置对话框
		void BackSetting();
		//曲线设置对话框
		void CurveSetting();
		//右键点击事件
		void contextMenuEvent(QContextMenuEvent *event);

	private:
		Ui::PlotMainWidget *_ui;
		PlotWidget *_plotwidget{nullptr};
		PropertyWidget *_prowidget{nullptr};

		QMenu *_menu;
		QAction *_datasetting;
		QAction *_curvesetting;
		QAction *_titlesetting;
		QAction *_axisetting;
		QAction *_backgroundsetting;
	};

}

#endif // PLOTMAINWIDGET_H
