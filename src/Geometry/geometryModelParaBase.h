/**
 * @file geometryModelParaBase.h
 * @brief 操作参数基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-24 11:19
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
#ifndef GEOMETRYMODELBASE_H_
#define GEOMETRYMODELBASE_H_

#include "geometryAPI.h"
#include "DataProperty/DataBase.h"

namespace Geometry
{
	/**
	 * @brief 操作参数类型枚举值
	 * @since 2.5.0
	 */
	enum GeometryParaType
	{
		GeometryParaNone = 0,			///< 无意义，用于默认参数
		GeometryParaCreateBox,			///< 创建长方体（包括立方体）的操作参数
		GeometryParaCreateCylinder,		///< 创建圆柱的操作参数
		GeometryParaCreateCone,			///< 创建锥体的操作参数
		GeometryParaCreateFillet,		///< 创建倒圆角的操作参数
		GeometryParaCreateSphere,		///< 创建球体的操作参数
		GeometryParaCreatePoint,		///< 创建点的操作参数
		GeometryParaCreateLine,			///< 创建线段的操作参数
		GeometryParaCreateFace,			///< 创建面的操作参数
		GeometryParaMakeChamfer,		///< 创建倒角的操作参数
		GeometryParaMakeVariableFillet,	///< 创建可变圆角的操作参数
		GeometryParaMakeBoolOperation,	///< 创建布尔运算（操作）的操作参数
		GeometryParaMakeMirrorFeature,	///< 创建镜像特征的操作参数
		GeometryParaMakeRotateFeature,	///< 创建旋转特征的操作参数
		GeometryParaMakeMoveFeature,	///< 创建移动的操作参数
		GeometryParaMakeMatrix,			///< 
		GeometryParaMakeExtrusion,		///< 创建拉伸特征的操作参数
		GeometryParaMakeLoft,			///< 
		GeometryParaMakeSweep,			///< 创建扫略特征的操作参数
		GeometryParaMakeRevol,			///< 创建旋转特征的操作参数
		GeometryParaSplitter,			///< 创建移除曲面的操作参数
		GeometryParaFillHole,			///< 创建填补孔洞的操作参数
		GeometryParaRemoveSurface,		///< 创建移除曲面的操作参数
		GeometryParaFillGap,			///< 
	};

	class GeometryData;
	/**
	 * @brief 操作参数基类
	 * @note 记录建模过程中的参数，可用于模型的边界修改
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeometryModelParaBase : public DataProperty::DataBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		GeometryModelParaBase();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometryModelParaBase() = default;
		/**
		 * @brief 获取操作参数类型
		 * @return GeometryParaType 返回操作参数类型
		 * @since 2.5.0
		 */
		GeometryParaType getParaType();
		/**
		 * @brief 通过字符串创建操作参数
		 * @param s 操作参数字符串
		 * @return GeometryModelParaBase* 返回操作参数对象
		 * @since 2.5.0
		 */
		static GeometryModelParaBase* createParaByString(QString s);

	protected:
		/**
		 * @brief 将操作类型转换为字符串
		 * @return QString 转换后的操作类型字符串
		 * @since 2.5.0
		 */
		QString typeToString();
	
	protected:
		/**
		 * @brief 操作参数类型
		 * @since 2.5.0
		 */
		GeometryParaType _type{ GeometryParaNone };
		/**
		 * @brief 几何数据管理类对象
		 * @since 2.5.0
		 */
		GeometryData* _geoData{};
	};




}


#endif