/**
 * @file PropertyList.h
 * @brief 属性列表类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-15 13:01
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
#ifndef PROPERTYLIST_H
#define PROPERTYLIST_H

#include "DataPropertyAPI.h"
#include <QList>
#include <QString>
#include <QColor>
//#include "PropertyPoint.h"

namespace DataProperty
{
	class PropertyBase;
	/**
	 * @brief 属性列表类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI PropertyList
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		PropertyList() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~PropertyList();
		/**
		 * @brief 获取属性列表中属性的个数
		 * @return int 
		 * @since 2.5.0
		 */
		int getPropertyCount();
		/**
		 * @brief 获取属性列表中索引为index的属性
		 * @param index 要获取属性的索引值
		 * @return PropertyBase* 返回获取到的属性
		 * @since 2.5.0
		 */
		PropertyBase* getPropertyAt(const int index);
		/**
		 * @brief 通过名字获取数值
		 * @param name 要获取属性的名字
		 * @return PropertyBase* 返回获取到的属性
		 * @since 2.5.0
		 */
		PropertyBase* getPropertyByName(const QString &name);
		/**
		 * @brief 拷贝属性列表的内容
		 * @param propList 要拷贝内容的源对象
		 * @since 2.5.0
		 */
		void copy(PropertyList* propList);
		/**
		 * @brief 在属性列表中添加整型属性
		 * @param name 属性的名称
		 * @param value 属性的值
		 * @since 2.5.0
		 */
		void appendProperty(QString name, int value);
		/**
		 * @brief 在属性列表中添加双精度属性
		 * @param name 属性的名称
		 * @param value 属性的值
		 * @since 2.5.0
		 */
		void appendProperty(QString name, double value);
		/**
		 * @brief 在属性列表中添加字符串属性
		 * @param name 属性的名称
		 * @param string 属性的值
		 * @since 2.5.0
		 */
		void appendProperty(QString name, QString string);
		/**
		 * @brief 在属性列表中添加颜色类型属性
		 * @param name 属性的名称
		 * @param color 属性的值
		 * @since 2.5.0
		 */
		void appendProperty(QString name, QColor color);
		/**
		 * @brief 在属性列表中添加布尔型属性
		 * @param name 属性的名称
		 * @param value 属性的值
		 * @since 2.5.0
		 */
		void appendProperty(QString name, bool value);
		/**
		 * @brief 在属性列表中添加点属性
		 * @param name 属性的名称
		 * @param c 属性的值（点坐标的三维数组）
		 * @since 2.5.0
		 */
		void appendProperty(QString name, double *c);
		/**
		 * @brief 在属性列表中添加点属性
		 * @param name 属性的名称
		 * @param x 点坐标的x值
		 * @param y 点坐标的y值
		 * @param z 点坐标的z值
		 * @since 2.5.0
		 */
		void appendProperty(QString name, double x, double y, double z);
		/**
		 * @brief 按名字移除属性
		 * @param name 属性的名称
		 * @return bool 返回是否成功移除的布尔值
		 * @since 2.5.0
		 */
		bool removeProperty(QString name);

	protected:
		/**
		 * @brief 在属性列表追加属性
		 * @param p 要追加的属性
		 * @return bool 返回是否追加成功的布尔值
		 * @since 2.5.0
		 */
		bool appendProperty(PropertyBase* p);
		/**
		 * @brief 清除属性列表
		 * @since 2.5.0
		 */
		void clearPropertyList();

    private:
		/**
		 * @brief 属性列表
		 * @since 2.5.0
		 */
		QList<PropertyBase*> _propertyList;
	};
}


#endif
