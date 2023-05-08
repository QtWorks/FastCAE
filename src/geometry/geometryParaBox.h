/**
 * @file geometryParaBox.h
 * @brief 创建立方体（长方体）操作类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 17:02
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
#ifndef _GEOMETRYPARABOX_H_
#define _GEOMETRYPARABOX_H_

#include "geometryModelParaBase.h"
#include <QString>

namespace Geometry
{
	/**
	 * @brief 创建立方体（长方体）操作类
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeometryParaBox : public GeometryModelParaBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		GeometryParaBox();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometryParaBox() = default;
		/**
		 * @brief 设置名称
		 * @param name 名称
		 * @since 2.5.0
		 */
		void setName(QString name);
		/**
		 * @brief 获取名称
		 * @return QString 返回名称
		 * @since 2.5.0
		 */
		QString getName();
		/**
		 * @brief 设置位置
		 * @param loc 位置
		 * @since 2.5.0
		 */
		void setLocation(double *loc);
		/**
		 * @brief 获取位置
		 * @param loc 返回位置
		 * @since 2.5.0
		 */
		void getLocation(double *loc);
		/**
		 * @brief 设置定形尺寸
		 * @param para 定形尺寸
		 * @since 2.5.0
		 */
		void setGeoPara(double *para);
		/**
		 * @brief 获取定形尺寸
		 * @param para 返回定形尺寸
		 * @since 2.5.0
		 */
		void getGeoPara(double *para);

		QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *parent) override;
		virtual void readDataFromProjectFile(QDomElement *e) override;

	private:
		/**
		 * @brief 名称
		 * @since 2.5.0
		 */
		QString _name{};
		/**
		 * @brief 位置
		 * @since 2.5.0
		 */
		double _location[3];
		/**
		 * @brief 定形尺寸
		 * @since 2.5.0
		 */
		double _geoPara[3];
	};
}

#endif