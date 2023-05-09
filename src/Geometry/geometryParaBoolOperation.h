/**
 * @file geometryParaBoolOperation.h
 * @brief 布尔操作参数类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 15:56
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
#ifndef _GEOMETRYPARABOOLOPERATION_H_
#define _GEOMETRYPARABOOLOPERATION_H_

#include "geometryModelParaBase.h"
#include "GeometryCommand/GeoCommandBool.h"
#include <QString>

namespace Geometry
{
	/**
	 * @brief 布尔操作参数类
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeometryParaBoolOperation : public GeometryModelParaBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		GeometryParaBoolOperation();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometryParaBoolOperation() = default;
		/**
		 * @brief 设置第一个操作对象
		 * @param body1 第一个操作对象
		 * @since 2.5.0
		 */
		void setInputBody1(QPair<Geometry::GeometrySet *, int> body1);
		/**
		 * @brief 获取第一个操作对象
		 * @return QPair<Geometry::GeometrySet *, int> 返回第一个操作对象
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> getBody1();
		/**
		 * @brief 设置第二个操作对象
		 * @param body2 第二个操作对象
		 * @since 2.5.0
		 */
		void setInputBody2(QPair<Geometry::GeometrySet *, int> body2);
		/**
		 * @brief 获取第二个操作对象
		 * @return QPair<Geometry::GeometrySet *, int> 返回第二个操作对象
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> getBody2();
		/**
		 * @brief 设置布尔操作类型
		 * @param b 布尔操作类型
		 * @since 2.5.0
		 */
		void setType(BoolType b);
		/**
		 * @brief 获取布尔操作类型
		 * @return BoolType 返回布尔操作类型
		 * @since 2.5.0
		 */
		BoolType getType();
		QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *parent) override;
		virtual void readDataFromProjectFile(QDomElement *e) override;
		/**
		 * @brief 布尔操作类型转换为字符串
		 * @param b 要转换的布尔操作类型
		 * @return QString 返回转换后的字符串
		 * @since 2.5.0
		 */
		QString BoolTypeToString(BoolType b);
		/**
		 * @brief 字符串转换为布尔操作类型
		 * @param s 要转换的字符串
		 * @return BoolType 返回转换后的布尔操作类型
		 * @since 2.5.0
		 */
		BoolType StringToBoolType(QString s);

	private:
		/**
		 * @brief 布尔操作类型
		 * @since 2.5.0
		 */
		BoolType _booltype;
		/**
		 * @brief 布尔操作的第一个几何对象
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> _body1;
		/**
		 * @brief 布尔操作的第二个几何对象
		 * @since 2.5.0
		 */
		QPair<Geometry::GeometrySet *, int> _body2;
	};
}

#endif