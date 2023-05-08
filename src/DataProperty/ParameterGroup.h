/**
 * @file ParameterGroup.h
 * @brief 参数组类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-09 15:44
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
#ifndef _PARAMETERGROUP_H_
#define _PARAMETERGROUP_H_

#include "ParameterList.h"
#include "ParameterBase.h"
#include <QDataStream>
#include <QString>

namespace DataProperty
{
	class ParameterBase;
	class DataBase;

	/**
	 * @brief 参数组类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI ParameterGroup : public ParameterList
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		ParameterGroup() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ParameterGroup() = default;
		/**
		 * @brief 拷贝data中的内容
		 * @param data 要拷贝的对象
		 * @since 2.5.0
		 */
		void copy(ParameterGroup* data);
		/**
		 * @brief 增加参数到参数组
		 * @param p 要增加的参数
		 * @since 2.5.0
		 */
		void appendParameter(ParameterBase* p) override;
		/**
		 * @brief 根据类型创建新的参数，并放入参数组
		 * @param type 要创建参数的类型
		 * @return ParameterBase* 返回创建的参数
		 * @since 2.5.0
		 */
		ParameterBase* appendParameter(ParaType type) override;
		/**
		 * @brief 设置参数组的名称
		 * @param des 要设置为参数组的名称
		 * @since 2.5.0
		 */
		void setDescribe(QString des);
		/**
		 * @brief 获取参数组的名称
		 * @return QString 参数组的名称
		 * @since 2.5.0
		 */
		QString getDescribe();
		/**
		 * @brief 设置参数组是否可见
		 * @param v 要设置参数组可见性的布尔值
		 * @since 2.5.0
		 */
		void setVisible(bool v);
		/**
		 * @brief 获取参数组的可见性
		 * @return bool 参数组的可见性
		 * @since 2.5.0
		 */
		bool isVisible();
		/**
		 * @brief 拷贝参数组的属性（可见性）
		 * @param g 要拷贝属性的源参数组
		 * @since 2.5.0
		 */
		void copyStates(ParameterGroup* g);
		/**
		 * @brief 将参数对象写入到工程文件
		 * @param doc 工程文件的QDomDocument对象
		 * @param parent 要追加该参数的父节点
		 * @since 2.5.0
		 */
		void writeParameters(QDomDocument* doc, QDomElement* parent) override;
		/**
		 * @brief 从工程文件中对应节点读取参数
		 * @param ele 工程文件中对应的节点对象
		 * @since 2.5.0
		 */
		void readParameters(QDomElement* ele) override;
		/**
		 * @brief 获取参数组的二进制流
		 * @param datas 参数组的二进制流
		 * @since 2.5.0
		 */
		virtual void dataToStream(QDataStream* datas) override;

	private:
		/**
		 * @brief 参数组的名称
		 * @since 2.5.0
		 */
		QString _describe{};
		/**
		 * @brief 参数组的可见性
		 * @since 2.5.0
		 */
		bool _visible{ true };
	};


}


#endif