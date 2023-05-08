/**
 * @file BCBase.h
 * @brief 边界条件基类，包含组件绑定、边界类型设置、xml文件相关内容读写
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 09:12
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
#ifndef _BCBASE_H_
#define _BCBASE_H_

#include "BCBaseAPI.h"
#include "DataProperty/DataBase.h"
#include "DataProperty/ComponentBase.h"
#include "BCType.h"

namespace MeshData
{
	class MeshData;
	class MeshSet;
}

namespace Geometry
{
	class GeoComponent;
}

namespace BCBase
{
	/**
	 * @brief 边界条件基类
	 * @since 2.5.0
	 */
	class BCBASEAPI BCBase : public DataProperty::DataBase
	{
	public:
		BCBase();
		~BCBase() = default;
		/**
		 * @brief 拷贝数据
		 * @param data 要拷贝的源数据
		 * @since 2.5.0
		 */
		virtual void copy(DataBase *data) override;
		/**
		 * @brief 绑定组件ID
		 * @param id 组件ID
		 * @since 2.5.0
		 */
		void bingdingComponentID(int id);
		/**
		 * @brief 获取绑定组件的ID
		 * @return int 组件ID
		 * @since 2.5.0
		 */
		int getComponentID();
		/**
		 * @brief 获取绑定组件的名称
		 * @return QString 组件名称
		 * @since 2.5.0
		 */
		QString getComponentName();
		/**
		 * @brief 获取绑定的组件对象（几何组件或网格组件）
		 * @return DataProperty::ComponentBase* 组件对象指针
		 * @since 2.5.0
		 */
		DataProperty::ComponentBase *getComponent();
		/**
		 * @brief 设置组件
		 * @since 2.5.0
		 */
		void setComponent(DataProperty::ComponentBase *);
		/**
		 * @brief 设置边界条件类型
		 * @param t 边界条件类型
		 * @since 2.5.0
		 */
		void setBCType(BCType t);
		/**
		 * @brief 获取边界条件类型
		 * @return BCType 边界条件类型
		 * @since 2.5.0
		 */
		BCType getBCType();

		virtual QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *parent) override;
		virtual void readDataFromProjectFile(QDomElement *ele) override;

	protected:
		BCType _BCtype{None};
		int _ComponentID{-1};

		DataProperty::ComponentBase *_component{};
		MeshData::MeshData *_mesh{};
	};
}

#endif