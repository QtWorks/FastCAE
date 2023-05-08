/**
 * @file ParameterColor.h
 * @brief 颜色类型参数类的头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 18:03
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
#ifndef _PARAMETERCOLOR_H_
#define _PARAMETERCOLOR_H_

#include "ParameterBase.h"
#include <QColor>

namespace DataProperty
{
	/**
	 * @brief 颜色类型参数类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI ParameterColor : public ParameterBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		ParameterColor();
		/**
		 * @brief 构造函数
		 * @param color 要赋予参数的值
		 * @since 2.5.0
		 */
		ParameterColor(QColor color);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ParameterColor() = default;
		/**
		 * @brief 从ori中拷贝内容
		 * @param ori 要拷贝内容的源参数对象
		 * @param valueOnly 是否仅仅拷贝值
		 * @since 2.5.0
		 */
		void copy(ParameterBase* ori, bool valueOnly /* = false */) override;
		/**
		 * @brief 设置参数的值
		 * @param c 要设置为参数的值
		 * @since 2.5.0
		 */
		void setColor(QColor c);
		/**
		 * @brief 设置参数的值
		 * @param c 要设置为参数的值
		 * @since 2.5.0
		 */
		void setColor(int* c);
		/**
		 * @brief 获取参数的值
		 * @return QColor 参数的值
		 * @since 2.5.0
		 */
		QColor getColor();
		/**
		 * @brief 获取参数的值赋给c
		 * @param c 要接受参数值的双精度浮点型数组
		 * @since 2.5.0
		 */
		void getColorF(double* c);
		/**
		 * @brief 判断对象是否与参数p值相等
		 * @param p 要比较的参数对象
		 * @return bool 
		 * @since 2.5.0
		 */
		bool isSameValueWith(ParameterBase* p) override;
		/**
		 * @brief 判断对象是否与参数p值相等
		 * @param p 要比较的参数对象
		 * @return bool 
		 * @since 2.5.0
		 */
		QString valueToString() override;
		/**
		 * @brief 将参数对象写入到工程文件
		 * @param doc 工程文件的QDomDocument对象
		 * @param parent 要追加该参数的父节点
		 * @since 2.5.0
		 */
		void writeParameter(QDomDocument* doc, QDomElement* parent) override;
		/**
		 * @brief 从工程文件中对应节点读取参数
		 * @param e 工程文件中对应的节点对象
		 * @since 2.5.0
		 */
		void readParameter(QDomElement* e) override;
		/**
		 * @brief 设置从字符串对象获取参数值（转换）
		 * @param v 要操作的字符串
		 * @attention 如果V是不合法，将不会有赋值操作
		 * @since 2.5.0
		 */
		void setValueFromString(QString v) override;


	private:
		/**
		 * @brief 参数的值
		 * @since 2.5.0
		 */
		QColor _color;
	};
}


#endif
