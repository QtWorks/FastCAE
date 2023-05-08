/**
 * @file ComponentBase.h
 * @brief 组件基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 14:56
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
#ifndef _COMPONENTBASE_H_
#define _COMPONENTBASE_H_

#include "DataPropertyAPI.h"
#include "DataBase.h"

namespace DataProperty
{
	/**
	 * @brief 组件类型枚举值
	 * @since 2.5.0
	 */
	enum ComponentType
	{
		MESH = 1, ///< 网格组件
		GEOMETRY  ///< 几何组件
	};

	/**
	 * @brief 组件基类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI ComponentBase : public DataBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @param type 组件类型
		 * @since 2.5.0
		 */
		ComponentBase(ComponentType type);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		virtual ~ComponentBase();
		/**
		 * @brief 获取组件类型
		 * @return ComponentType 返回组件类型
		 * @since 2.5.0
		 */
		ComponentType getComponentType();
		/**
		 * @brief 设置组件id
		 * @param id 组件id
		 * @since 2.5.0
		 */
		void setID(int id);
		/**
		 * @brief 获取最大id
		 * @return int 最大组件id
		 * @since 2.5.0
		 */
		static int getMaxID();
		/**
		 * @brief 重置组件id
		 * @since 2.5.0
		 */
		static void resetMaxID();
		/**
		 * @brief 通过id获取组件类型
		 * @param id
		 * @return ComponentType 返回组件类型
		 * @since 2.5.0
		 */
		static ComponentType getComponentTypeByID(int id);
		/**
		 * @brief 组件类型转字符串
		 * @param cpType 要转换的组件类型
		 * @return QString 返回转换后的字符串
		 * @since 2.5.0
		 */
		static QString componentTypeToString(ComponentType cpType);
		/**
		 * @brief 字符串转组件类型
		 * @param sType 要转换的字符串
		 * @return ComponentType 返回转换后的组件类型
		 * @since 2.5.0
		 */
		static ComponentType stringToComponentType(QString sType);

	private:
		/**
		 * @brief 组件id与类型的对应哈希表
		 * @since 2.5.0
		 */
		static QHash<int, ComponentType> IDType;
		/**
		 * @brief 组件当前最大ID值
		 * @since 2.5.0
		 */
		static int currMaxID;
		/**
		 * @brief 组件类型
		 * @since 2.5.0
		 */
		ComponentType _type;
	};
}

#endif