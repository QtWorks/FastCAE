/**
 * @file GeoCommandCreateBox.h
 * @brief 创建立方体（长方体）命令类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 17:07
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
#ifndef GEOCREATEBOXCOMMAND_H_
#define GEOCREATEBOXCOMMAND_H_

#include "geometryCommandAPI.h"
#include "GeoCommandBase.h"
#include <QString>

namespace Geometry
{
	class GeometrySet;
}

namespace Command
{
	/**
	 * @brief 创建立方体（长方体）命令类
	 * @since 2.5.0
	 */
	class GEOMETRYCOMMANDAPI CommandCreateBox : public GeoCommandBase
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @since 2.5.0
		 */
		CommandCreateBox(GUI::MainWindow *m, MainWidget::PreWindow *p);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~CommandCreateBox() = default;
		/**
		 * @brief 设置名称
		 * @param name 名称
		 * @since 2.5.0
		 */
		void setName(QString name);
		/**
		 * @brief 设置位置
		 * @param loca 位置
		 * @since 2.5.0
		 */
		void setLocation(double *loca);
		/**
		 * @brief 设置定形尺寸
		 * @param para 定形尺寸
		 * @since 2.5.0
		 */
		void setGeoPara(double *para);

		bool execute() override;
		void undo() override;
		void redo() override;
		void releaseResult() override;

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
		double _loaction[3];
		/**
		 * @brief 定形尺寸
		 * @since 2.5.0
		 */
		double _geoPara[3];

		Geometry::GeometrySet *_res{};
	};
}

#endif