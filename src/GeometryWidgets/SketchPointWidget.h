/**
 * @file SketchPointWidget.h
 * @brief 草绘模式点输入对话框类的头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-29 15:12
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
#ifndef SKETCHWIDGETPOINT_H_
#define SKETCHWIDGETPOINT_H_

#include "geoDialogBase.h"
#include "geometryWidgetsAPI.h"

namespace Command
{
	class SketchCreater;
}

namespace Ui
{
	class SketchPointWidget;
}

namespace Geometry
{
	class GeometryData;
}

namespace GeometryWidget
{
	/**
	 * @brief 草绘模式点输入对话框类
	 * @since 2.5.0
	 */
	class GEOMETRYWIDGETSAPI SketchPointWidget : public GeoDialogBase
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param pre 前处理窗口对象
		 * @param c 草绘对象
		 * @since 2.5.0
		 */
		SketchPointWidget(GUI::MainWindow *m, MainWidget::PreWindow *pre, Command::SketchCreater *c);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~SketchPointWidget();

	private slots:
		/**
		 * @brief 添加点按钮的响应槽函数
		 * @since 2.5.0
		 */
		void on_addButton_clicked();

	private:
		/**
		 * @brief 草绘对象
		 * @since 2.5.0
		 */
		Command::SketchCreater *_creater{};
		/**
		 * @brief ui
		 * @since 2.5.0
		 */
		Ui::SketchPointWidget *_ui{};
		/**
		 * @brief 几何数据
		 * @since 2.5.0
		 */
		Geometry::GeometryData *_geoData{};
	};

}

#endif // !SKETCHWIDGETPOINT_H_
