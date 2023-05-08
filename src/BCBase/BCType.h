/**
 * @file BCType.h
 * @brief 边界条件类型
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 08:53
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
#ifndef _BCTYPE_H_
#define _BCTYPE_H_

#include <QString>
#include "BCBaseAPI.h"

namespace BCBase
{
	/**
	 * @brief 边界条件类型枚举类型
	 * @since 2.5.0
	 */
	enum BCType
	{
		None = 0, ///< 无

		Pressure,		   ///< 压力
		Velocity,		   ///< 速度
		Temperature,	   ///< 温度
		FixSupport,		   ///< 固定支撑
		Displacement,	   ///< 位移
		AngleVelocity,	   ///< 角速度
		Rotation,		   ///< 转角
		Acceleration,	   ///< 加速度
		AngleAcceleration, ///< 角加速度
		Inlet,			   ///< 入口
		Outlet,			   ///< 出口
		Symmetry,		   ///< 对称面
		Wall,			   ///< 壁面
		End,			   ///< 标记位（当枚举值作为int处理时，从None到End为内置边界条件类型）
		UserDef,		   ///< 用户自定义

	};

	/**
	 * @brief 边界条件枚举值转换为字符串
	 * @param t 枚举值
	 * @return QString 返回转换后的字符串
	 * @since 2.5.0
	 */
	extern QString BCBASEAPI BCTypeToString(BCType t);

	extern QString BCBASEAPI BCIconByType(BCType t);

	extern BCType BCBASEAPI StringToBCType(QString s);

}

#endif