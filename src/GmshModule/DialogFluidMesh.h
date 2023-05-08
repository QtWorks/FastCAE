/**
 * @file DialogFluidMesh.h
 * @brief 流体网格划分对话框类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-31 18:14
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
#ifndef DIALOGFLUIDMESH_H
#define DIALOGFLUIDMESH_H

#include "GmshDialogBase.h"
#include <QDialog>

namespace Ui
{
	class DialogFluidMesh;
}

namespace GUI
{
	class MainWindow;
}

namespace MainWidget
{
	class PreWindow;
}

namespace Geometry
{
	class GeometrySet;
	class GeometryData;
}

namespace GeometryWidget
{
	class GeoPointWidget;
}

namespace Gmsh
{
	/**
	 * @brief 流体网格划分对话框类
	 * @since 2.5.0
	 */
	class DialogFluidMesh : public GmshDialogBase
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param pre 前处理窗口对象
		 * @param index
		 * @since 2.5.0
		 */
		DialogFluidMesh(GUI::MainWindow *m, MainWidget::PreWindow *pre, int index = -1);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~DialogFluidMesh();

	private slots:
		/**
		 * @brief 几何选择按钮槽函数
		 * @since 2.5.0
		 */
		void on_geoSelectSurface_clicked();
		void shapeSlected(Geometry::GeometrySet *set, int index);
		/**
		 * @brief 点选择按钮槽函数
		 * @since 2.5.0
		 */
		void pointWidgetClicked(GeometryWidget::GeoPointWidget *);

	private:
		//		void closeEvent(QCloseEvent *) override;
		void accept() override;
		void reject() override;
		/**
		 * @brief 判断流体域的起始点与终点是否重合
		 * @return bool 返回判断结果
		 * @since 2.5.0
		 */
		bool fluidFieldIsSrue();

	private:
		/**
		 * @brief ui
		 * @since 2.5.0
		 */
		Ui::DialogFluidMesh *_ui;
		QMultiHash<Geometry::GeometrySet *, int> _solidHash{};
		/**
		 * @brief 几何数据
		 * @since 2.5.0
		 */
		Geometry::GeometryData *_geoData;
		bool _selectBody{false};
		/**
		 * @brief 流体域起始点选择窗口部件
		 * @since 2.5.0
		 */
		GeometryWidget::GeoPointWidget *_minPoint{};
		/**
		 * @brief 流体域终点选择窗口部件
		 * @since 2.5.0
		 */
		GeometryWidget::GeoPointWidget *_maxPoint{};
	};
}
#endif // DIALOGFLUIDMESH_H
