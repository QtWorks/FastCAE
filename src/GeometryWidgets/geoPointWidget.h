/**
 * @file geoPointWidget.h
 * @brief 自定义三维坐标点拾取部件类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-29 14:23
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
#ifndef _GEOPOINTWIDGET_H_
#define _GEOPOINTWIDGET_H_

#include <QWidget>
#include <QPair>
#include "GeometryWidgets/geometryWidgetsAPI.h"

namespace GUI
{
	class MainWindow;
}
namespace MainWidget
{
	class PreWindow;
}
namespace Ui
{
	class geoPointWidget;
}
namespace Geometry
{
	class GeometrySet;
}

namespace GeometryWidget
{
	/**
	 * @brief 自定义三维坐标点拾取部件类
	 * @since 2.5.0
	 */
	class GEOMETRYWIDGETSAPI GeoPointWidget : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @since 2.5.0
		 */
		GeoPointWidget(GUI::MainWindow *m, MainWidget::PreWindow *p);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeoPointWidget();
		/**
		 * @brief 获取坐标值
		 * @param coor 要存储坐标值的数组
		 * @return bool 返回获取结果
		 * @since 2.5.0
		 */
		bool getCoordinate(double *coor);
		void handleProcess(bool h);
		/**
		 * @brief 设置坐标值
		 * @param coor 坐标值的数组
		 * @since 2.5.0
		 */
		void setCoordinate(double *coor);

	signals:
		/**
		 * @brief 部件内选择点的按钮被点击后会触发该信号
		 * @since 2.5.0
		 */
		void buttonCkicked(GeoPointWidget *);
		/**
		 * @brief 部件内选择点的按钮被点击后会触发该信号，并置为点选模式（ModuleBase::GeometryPoint）
		 * @since 2.5.0
		 */
		void setSelectMode(int);
		/**
		 * @brief 部件类的析构函数会触发该信号
		 * @since 2.5.0
		 */
		void clearGeometryHighLightSig();
		/**
		 * @brief 前处理窗口选择点后会触发该信号
		 * @since 2.5.0
		 */
		void highLightGeometryPointSig(Geometry::GeometrySet *, int, bool);

	private slots:
		/**
		 * @brief 部件内选择点的按钮的响应槽函数
		 * @since 2.5.0
		 */
		void on_geoSelectPoint_clicked();
		/**
		 * @brief 前处理窗口选择几何形状的响应槽函数
		 * @bug 未对选择的几何形状过滤且用户依然可以手动切换选择模式
		 * @since 2.5.0
		 */
		void selectPoint(Geometry::GeometrySet *, int);

	private:
		/**
		 * @brief ui
		 * @since 2.5.0
		 */
		Ui::geoPointWidget *_ui;
		/**
		 * @brief 主窗口对象
		 * @since 2.5.0
		 */
		GUI::MainWindow *_mainWindow{};
		/**
		 * @brief 前处理窗口对象
		 * @since 2.5.0
		 */
		MainWidget::PreWindow *_preWindow{};
		/**
		 * @brief 选择的点形状
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> _selectedPoint{nullptr, -1};

		bool _handle{true};
	};
}

#endif