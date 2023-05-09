/**
 * @file geometryDatum.h
 * @brief 基准（参考）形状类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-25 09:58
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
#ifndef GEOMETRYDATUMPLANE_H_
#define GEOMETRYDATUMPLANE_H_

#include "geometryAPI.h"
#include "geometrySet.h"

class TopoDS_Shape;

namespace Geometry
{
	/**
	 * @brief 基准形状类型
	 * @since 2.5.0
	 */
	enum DatumType
	{
		DatumNone,		///< 无定义，用于默认参数
		DatumPoint,		///< 基准点
		DatumAxis,		///< 基准轴
		DatumPlane,		///< 基准平面
	};

	/**
	 * @brief 基准形状类
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeometryDatum : public GeometrySet
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		GeometryDatum();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometryDatum();
		/**
		 * @brief 设置基准类型
		 * @param t 基准类型
		 * @since 2.5.0
		 */
		void setDatumType(DatumType t);
		/**
		 * @brief 获取基准类型
		 * @return DatumType 返回基准类型
		 * @since 2.5.0
		 */
		DatumType getDatumType();

		virtual QDomElement& writeToProjectFile(QDomDocument* doc, QDomElement* ele, bool isDisp /* = false */) override;
		virtual void readDataFromProjectFile(QDomElement* e, bool isDiso /* = false */);
		/**
		 * @brief 将基准类型转换为字符串
		 * @param t 要转换的基准类型
		 * @return QString 返回转换后的字符串
		 * @since 2.5.0
		 */
		static QString datumTypeToString(DatumType t);
		/**
		 * @brief 将字符串转换为基准类型
		 * @param s 要转换的字符串
		 * @return DatumType 返回转换后的基准类型
		 * @attention 如果传入的字符串非法，则返回DatumNone
		 * @since 2.5.0
		 */
		static DatumType datumTypeFromString(QString s);

	private:
		/**
		 * @brief 基准类型
		 * @since 2.5.0
		 */
		DatumType _type{ DatumNone };
	};

}

#endif
