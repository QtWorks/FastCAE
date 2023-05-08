/**
 * @file ParameterBool.h
 * @brief 布尔类型参数类的头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 17:55
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
#ifndef _PARAMEYTERBOOL_H_
#define _PARAMEYTERBOOL_H_

#include "ParameterBase.h"

namespace DataProperty
{
	/**
	 * @brief 布尔类型参数类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI ParameterBool : public ParameterBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		ParameterBool();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ParameterBool() = default;
		/**
		 * @brief 从ori中拷贝内容
		 * @param ori 要拷贝内容的源参数对象
		 * @param valueOnly 是否仅仅拷贝值
		 * @since 2.5.0
		 */
		void copy(ParameterBase* ori, bool valueOnly = false) override;
		/**
		 * @brief 设置参数的值
		 * @param ok 要设置为参数的值
		 * @since 2.5.0
		 */
		void setValue(bool ok);
		/**
		 * @brief 获取参数的值
		 * @return bool 参数的值
		 * @since 2.5.0
		 */
		bool getValue();
		/**
		 * @brief 判断对象是否与参数p值相等
		 * @param p 要比较的参数对象
		 * @return bool 返回参数的比较结果（是否相等）
		 * @since 2.5.0
		 */
		bool isSameValueWith(ParameterBase* p) override;
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
		 * @brief 将参数转换为字符串类型（QString）值
		 * @return QString 转换后得到的字符串值
		 * @since 2.5.0
		 */
		QString valueToString() override;
		/**
		 * @brief 设置从字符串对象获取参数值（转换）
		 * @param v 要操作的字符串
		 * @attention 如果V是true（忽略大小写）之外的值，都将被转换为false
		 * @since 2.5.0
		 */
		void setValueFromString(QString v) override;

	private:
		/**
		* @brief 参数的值
		* @since 2.5.0
		*/
		bool _value{ false };

	};
}


#endif