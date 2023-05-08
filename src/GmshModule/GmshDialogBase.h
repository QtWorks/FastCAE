/**
 * @file GmshDialogBase.h
 * @brief 网格划分对话框基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-31 18:21
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
#ifndef _GMSHDIALOG_BASE__H_
#define _GMSHDIALOG_BASE__H_

#include "GeometryWidgets/geoDialogBase.h"
#include "GmshModuleAPI.h"
#include <QList>

namespace Py
{
	class PythonAgent;
}

namespace MeshData
{
	class MeshKernal;
}

namespace Gmsh
{
	//	class PhysicalsGroups;
	class LocalDensity;

	/**
	 * @brief 网格划分对话框基类
	 * @since 2.5.0
	 */
	class /*GMSHAPI*/ GmshDialogBase : public GeometryWidget::GeoDialogBase
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param pre 前处理窗口对象
		 * @since 2.5.0
		 */
		GmshDialogBase(GUI::MainWindow *m, MainWidget::PreWindow *pre);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GmshDialogBase();

		//		QList<PhysicalsGroups*>* getPhysicalsGroups();
		/**
		 * @brief 获取区域加密信息
		 * @since 2.5.0
		 */
		QList<LocalDensity *> *getLocalDesities();

	signals:
		void showDialog(QDialog *);
		void highLightMeshKernal(MeshData::MeshKernal *);

	protected:
		// void appendPhysicals();
		/**
		 * @brief 提交网格加密相关的python脚本
		 * @since 2.5.0
		 */
		void appendLocalDesities();

	protected:
		/**
		 * @brief python解释器交互对象
		 * @since 2.5.0
		 */
		Py::PythonAgent *_pyAgent{};
		//		QList<PhysicalsGroups*> _physicalsGroups{};
		/**
		 * @brief 区域网格加密信息类别
		 * @since 2.5.0
		 */
		QList<LocalDensity *> _localDensities;
	};

}

#endif