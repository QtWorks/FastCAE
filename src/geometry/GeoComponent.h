/**
 * @file GeoComponent.h
 * @brief 几何组件类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 13:41
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
#ifndef _GEOCOMPONENT_H_
#define _GEOCOMPONENT_H_

#include "geometryAPI.h"
#include "DataProperty/ComponentBase.h"
#include <qhash.h>

class vtkPolyData;

namespace Geometry
{
	/**
	 * @brief 几何组件类型
	 * @since 2.5.0
	 */
	enum GeoComponentType
	{
		Node,	 ///< 点
		Line,	 ///< 线
		Surface, ///< 面
		Body	 ///< 体
	};

	class GeometrySet;

	/**
	 * @brief 几何组件类
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeoComponent : public DataProperty::ComponentBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @param name 组件名称
		 * @param type 组件类别
		 * @since 2.5.0
		 */
		GeoComponent(QString name, GeoComponentType type);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeoComponent();
		/**
		 * @brief 设置几何组件的类型
		 * @param type 组件类型
		 * @since 2.5.0
		 */
		void setType(GeoComponentType type);
		/**
		 * @brief 获取组件的类型
		 * @return GeoComponentType 返回组件类型
		 * @since 2.5.0
		 */
		GeoComponentType getGCType();
		/**
		 * @brief 添加选择项
		 * @param items 要添加的几何形状列表
		 * @since 2.5.0
		 */
		void appendSelectedItem(QMultiHash<GeometrySet *, int> &items);
		/**
		 * @brief 添加选择项
		 * @param geoSet 要添加的几何形状
		 * @param itemIndex 几何形状的id
		 * @since 2.5.0
		 */
		void appendSelectedItem(GeometrySet *geoSet, int itemIndex);
		/**
		 * @brief 添加选择项
		 * @param geoSet 要添加的几何形状
		 * @param itemIndexs 几何形状的id列表
		 * @since 2.5.0
		 */
		void appendSelectedItem(GeometrySet *geoSet, QList<int> &itemIndexs);
		/**
		 * @brief 设置几何组件的形状列表
		 * @param items 几何组件的形状列表
		 * @since 2.5.0
		 */
		void setSelectedItems(QMultiHash<GeometrySet *, int> &items);
		/**
		 * @brief 获取几何组件形状列表
		 * @return QMultiHash<GeometrySet *, int>& 返回形状列表
		 * @since 2.5.0
		 */
		QMultiHash<GeometrySet *, int> &getSelectedItems();
		/**
		 * @brief 字符串转几何组件类型
		 * @param stype 要转换的字符串
		 * @return GeoComponentType 返回转换后的几何类型
		 * @since 2.5.0
		 */
		static GeoComponentType stringTogcType(QString stype);
		/**
		 * @brief 几何组件类型转字符串
		 * @param type 要转换的几何组件类型
		 * @return QString 返回转换后的字符串
		 * @since 2.5.0
		 */
		static QString gcTypeToString(GeoComponentType type);
		virtual QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *root) override;
		virtual void readDataFromProjectFile(QDomElement *root) override;

	private:
		/**
		 * @brief 几何组件类型
		 * @since 2.5.0
		 */
		GeoComponentType _type;
		/**
		 * @brief 几何组件的几何形状列表
		 * @since 2.5.0
		 */
		QMultiHash<GeometrySet *, int> _selectedItems{};
	};
}

#endif
