/**
 * @file ParameterInt.h
 * @brief 整型参数类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-09 16:01
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
#ifndef _PARAMETERINT_H_
#define _PARAMETERINT_H_

#include "ParameterBase.h"

namespace DataProperty
{
	/**
	 * @brief 整型参数类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI ParameterInt : public ParameterBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		ParameterInt();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ParameterInt() = default;
		/**
		 * @brief 从ori中拷贝内容
		 * @param ori 要拷贝内容的源参数对象
		 * @param valueOnly 是否仅仅拷贝值
		 * @since 2.5.0
		 */
		void copy(ParameterBase* ori, bool valueOnly = false) override;
	    /**
	     * @brief 设置参数的值
	     * @param v 要设置为参数的值
	     * @since 2.5.0
	     */
		void setValue(int v);
		/**
		 * @brief 获取参数的值
		 * @return int 参数的值
		 * @since 2.5.0
		 */
		int getValue();
		/**
		 * @brief 设置参数的范围
		 * @param range 参数的范围
		 * @since 2.5.0
		 */
		void setRange(int* range);
		/**
		 * @brief 获取参数的范围
		 * @param range 参数的范围
		 * @since 2.5.0
		 */
		void getRange(int* range);
		/**
		 * @brief 设置参数的量纲
		 * @param unit 要作为参数量纲的字符串
		 * @since 2.5.0
		 */
		void setUnit(QString unit);
		/**
		 * @brief 获取参数的量纲
		 * @return QString 
		 * @since 2.5.0
		 */
		QString getUnit();
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
		 * @attention 转换失败时会将参数值设置为0
		 * @since 2.5.0
		 */
		void setValueFromString(QString v);

	private:
		/**
		 * @brief 参数的值
		 * @since 2.5.0
		 */
		int _value{ 0 };
		/**
		 * @brief 参数的范围
		 * @since 2.5.0
		 */
		int _range[2];
		/**
		 * @brief 参数的量纲
		 * @since 2.5.0
		 */
		QString _unit{};
	};
}


#endif
