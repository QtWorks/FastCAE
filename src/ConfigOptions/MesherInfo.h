/**
 * @file MesherInfo.h
 * @brief 网格剖分器信息类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 16:45
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
#ifndef _MESHERINFO_H_
#define _MESHERINFO_H_

#include "ConfigOptionsAPI.h"
#include "DataProperty/DataBase.h"
#include <QString>

namespace ConfigOption
{
	/**
	 * @brief 网格剖分器信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI MesherInfo: public DataProperty::DataBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		MesherInfo();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~MesherInfo() = default;
		/**
		 * @brief 获取网格剖分器的名称
		 * @return QString 网格剖分器的名称
		 * @since 2.5.0
		 */
		QString getMesherName();
		/**
		 * @brief 获取网格剖分器的模板文件
		 * @return QString 网格剖分器的模板文件
		 * @since 2.5.0
		 */
		QString getTemplate();
		/**
		 * @brief 获取网格剖分器的输出文件
		 * @return QString 网格剖分器的输出文件
		 * @since 2.5.0
		 */
		QString getOutput();
		/**
		 * @brief 从xml文件节点处读取网格剖分器的信息
		 * @param ele xml文件的节点对象
		 * @since 2.5.0
		 */
		void readParameters(QDomElement* ele) override;
		/**
		 * @brief 将网格剖分器的信息写入到xml配置文件
		 * @param doc xml配置文件对象
		 * @param parent 要追加当前网格剖分器信息的父节点
		 * @since 2.5.0
		 */
		void writeParameters(QDomDocument* doc, QDomElement* parent) override;


	private:

	private:
		/**
		 * @brief 网格剖分器的名称
		 * @since 2.5.0
		 */
		QString _mesherName{};
		/**
		 * @brief 网格剖分器的模板文件
		 * @since 2.5.0
		 */
		QString _template{};
		/**
		 * @brief 网格剖分器的输出文件
		 * @since 2.5.0
		 */
		QString _output{};

	};

}



#endif