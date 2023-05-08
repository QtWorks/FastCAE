/**
 * @file dialogBoolOperation.h
 * @brief 布尔操作对话框头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 18:38
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
#ifndef DIALOGBOOLOPERATION_H_
#define DIALOGBOOLOPERATION_H_

#include "geoDialogBase.h"
#include "GeometryCommand/GeoCommandBool.h"

namespace Ui
{
	class BoolOptionDialog;
}

namespace Geometry
{
	class GeometryData;
	class GeometrySet;
}

namespace GeometryWidget
{
	/**
	 * @brief 布尔操作对话框类
	 * @since 2.5.0
	 */
	class GEOMETRYWIDGETSAPI BoolOpertionDialog : public GeoDialogBase
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @since 2.5.0
		 */
		BoolOpertionDialog(GUI::MainWindow *m, MainWidget::PreWindow *p);
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @param set 几何形状对象
		 * @since 2.5.0
		 */
		BoolOpertionDialog(GUI::MainWindow *m, MainWidget::PreWindow *p, Geometry::GeometrySet *set);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~BoolOpertionDialog();
		/**
		 * @brief 设置布尔操作的类型
		 * @param t 布尔操作的类型
		 * @since 2.5.0
		 */
		void setType(BoolType t);

	private slots:
		/**
		 * @brief 选择几何体2的按键槽函数
		 * @since 2.5.0
		 */
		void on_geoSelectSurface_clicked();
		/**
		 * @brief 选择几何体1的按键槽函数
		 * @since 2.5.0
		 */
		void on_geoSelectSurface_1_clicked();
		void shapeSlected(Geometry::GeometrySet *, int) override;

	private:
		//		void closeEvent(QCloseEvent *);
		void reject() override;
		void accept() override;
		/**
		 * @brief 布尔操作类型转字符串
		 * @param n 布尔操作类型
		 * @return QString 返回转换后的字符串
		 * @since 2.5.0
		 */
		QString booltypeToString(BoolType n);

	private:
		/**
		 * @brief 对话框ui
		 * @since 2.5.0
		 */
		Ui::BoolOptionDialog *_ui{};
		/**
		 * @brief 布尔类型操作
		 * @since 2.5.0
		 */
		BoolType _type{BoolNone};

		/**
		 * @brief 选择第一个几何形状
		 * @since 2.5.0
		 */
		bool _selectBody1{false};
		/**
		 * @brief 选择第二个几何形状
		 * @since 2.5.0
		 */
		bool _selectBody2{false};

		/**
		 * @brief 第一个几何形状
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> _bodypair1{};
		/**
		 * @brief 第二个几何形状
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> _bodypair2{};
	};
}

#endif