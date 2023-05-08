/**
 * @file GeometryThreadBase.h
 * @brief 几何文件交换类的线程基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-18 15:33
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
#ifndef _GEOMETRYTHREADBASE_H_
#define _GEOMETRYTHREADBASE_H_

#include "ModuleBase/ThreadTask.h"
#include "GeometryDataExchangeAPI.h"
#include "ModuleBase/messageWindowBase.h"

namespace Geometry
{
	/**
	 * @brief 几何文件交换的操作类别枚举类
	 * @since 2.5.0
	 */
	enum GeometryOperation
	{
		GEOMETRY_NONE, ///< 无操作
		GEOMETRY_READ, ///< 读操作
		GEOMETRY_WRITE ///< 写操作
	};

	class GeometrySet;

	/**
	 * @brief 几何文件交换类的线程基类
	 * @since 2.5.0
	 */
	class GEOMETRYDATAEXCHANGEAPI GeometryThreadBase : public ModuleBase::ThreadTask
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mw 主窗口对象
		 * @param res 几何形状列表
		 * @since 2.5.0
		 */
		GeometryThreadBase(GUI::MainWindow *mw, QList<Geometry::GeometrySet *> &res);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		virtual ~GeometryThreadBase();
		/**
		 * @brief
		 * @since 2.5.0
		 */
		void defaultGeometryFinished();
		/**
		 * @brief 获取几何形状的列表
		 * @return QList<GeometrySet*>& 返回几何形状的特征
		 * @since 2.5.0
		 */
		QList<GeometrySet *> &getResult();

	signals:
		void updateGeometryTree();
		void updateActionsStates();
		void ShowSetSig(Geometry::GeometrySet *s, bool r = true);
		void showGeometryMessageSig(ModuleBase::Message);
		void updatePreGeometryActor();

	private:
		/**
		 * @brief 几何形状（特征）的列表
		 * @since 2.5.0
		 */
		QList<Geometry::GeometrySet *> &_result;
	};
}

#endif
