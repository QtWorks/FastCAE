/**
 * @file geometryDialogFactory.h
 * @brief 几何相关对话框的工厂类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-29 14:05
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
#ifndef _GEOMETRYDUALOGFACTORY_H__
#define _GEOMETRYDUALOGFACTORY_H__

#include "geometryWidgetsAPI.h"

class QDialog;

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
}

namespace GeometryWidget
{
	/**
	 * @brief 几何相关对话框的工厂类
	 * @since 2.5.0
	 */
	class GEOMETRYWIDGETSAPI GeometryDialogFactory
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		GeometryDialogFactory() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometryDialogFactory() = default;
		/**
		 * @brief 创建对话框
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @param set 几何形状
		 * @return QDialog* 返回创建的对话框
		 * @attention 如果判断不通过，该函数会返回nullptr
		 * @since 2.5.0
		 */
		static QDialog *editGeometryDialog(GUI::MainWindow *m, MainWidget::PreWindow *p, Geometry::GeometrySet *set);
	};

}

#endif // !_GEOMETRYDUALOGFACTORY_H_
