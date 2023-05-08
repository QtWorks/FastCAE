/**
 * @file GeoCommandBool.h
 * @brief 布尔操作命令类的头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 16:12
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
#ifndef GEOCOMMANDBOOL_H_
#define GEOCOMMANDBOOL_H_

#include "geometryCommandAPI.h"
#include "GeoCommandBase.h"
#include <QPair>

/**
 * @brief 布尔操作类型枚举值
 * @since 2.5.0
 */
enum BoolType
{
	BoolNone,	///< 无操作
	BoolCut,	///< 布尔求差操作
	BoolFause,	///< 布尔求和操作
	BoolCommon, ///< 布尔求交操作
};

class TopoDS_Shape;

namespace Geometry
{
	class GeometrySet;
}

namespace Command
{
	/**
	 * @brief 布尔操作命令类
	 * @since 2.5.0
	 */
	class GEOMETRYCOMMANDAPI CommandBool : public GeoCommandBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @since 2.5.0
		 */
		CommandBool(GUI::MainWindow *m, MainWidget::PreWindow *p);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~CommandBool() = default;
		/**
		 * @brief 设置布尔操作类型
		 * @param t 布尔操作类型
		 * @since 2.5.0
		 */
		void setType(BoolType t);
		// void setInputBody(Geometry::GeometrySet* b1, Geometry::GeometrySet* b2);
		/**
		 * @brief 设置布尔操作的第一个实体
		 * @param solid1 第一个实体对象
		 * @since 2.5.0
		 */
		void setSolid1(QPair<Geometry::GeometrySet *, int> solid1);
		/**
		 * @brief 设置布尔操作的第二个实体
		 * @param solid2 第二个实体对象
		 * @since 2.5.0
		 */
		void setSolid2(QPair<Geometry::GeometrySet *, int> solid2);
		bool execute() override;
		void undo() override;
		void redo() override;
		void releaseResult() override;

	private:
		/**
		 * @brief 布尔求差
		 * @return TopoDS_Shape* 返回布尔运算后的形状
		 * @since 2.5.0
		 */
		TopoDS_Shape *cut();
		/**
		 * @brief 布尔求和
		 * @return TopoDS_Shape* 返回布尔运算后的形状
		 * @since 2.5.0
		 */
		TopoDS_Shape *fause();
		/**
		 * @brief 布尔求交
		 * @return TopoDS_Shape* 返回布尔运算后的形状
		 * @since 2.5.0
		 */
		TopoDS_Shape *common();

	private:
		/*	Geometry::GeometrySet* _body1{};
			Geometry::GeometrySet* _body2{};*/
		/**
		 * @brief 布尔操作的第一个实体
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> _solid1{};
		/**
		 * @brief 布尔操作的第二个实体
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> _solid2{};
		/**
		 * @brief 布尔操作类型
		 * @since 2.5.0
		 */
		BoolType _type{BoolNone};

		Geometry::GeometrySet *_result{};
	};
}

#endif