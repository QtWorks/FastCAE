/**
 * @file geoDialogBase.h
 * @brief 几何操作对话框基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 18:16
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
#ifndef GEODIALOGBASE_H_
#define GEODIALOGBASE_H_

#include "geometryWidgetsAPI.h"
#include "SelfDefObject/QFDialog.h"
#include "ModuleBase/ModuleType.h"

class QDialogButtonBox;

namespace MainWidget
{
	class PreWindow;
}
namespace GUI
{
	class MainWindow;
}
namespace Geometry
{
	class GeometryData;
	class GeometrySet;
}

namespace Py
{
	class PythonAgent;
}

class vtkActor;

namespace GeometryWidget
{
	/**
	 * @brief 几何操作对话框基类
	 * @since 2.5.0
	 */
	class GEOMETRYWIDGETSAPI GeoDialogBase : public QFDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param p 前处理窗口
		 * @param keySig 是否设置键盘事件
		 * @param restoreselectmode
		 * @since 2.5.0
		 */
		GeoDialogBase(GUI::MainWindow *m, MainWidget::PreWindow *p, bool keySig = true, bool restoreselectmode = true);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeoDialogBase();
		/**
		 * @brief 判断是否为编辑模式
		 * @return bool 返回判断结果
		 * @since 2.5.0
		 */
		bool isEdit();
	signals:

		void setSelectMode(int);
		// delete***********
		void updateGraphOptions();
		void highLightGeometrySet(Geometry::GeometrySet *set, bool on);
		void highLightGeometryPoint(Geometry::GeometrySet *set, int index, QList<vtkActor *> *);
		void highLightGeometryEdge(Geometry::GeometrySet *set, int index, QList<vtkActor *> *);
		void highLightGeometryFace(Geometry::GeometrySet *set, int index, QList<vtkActor *> *);
		//***********
		void showGeometry(Geometry::GeometrySet *set);
		void hideGeometry(Geometry::GeometrySet *set);
		void updateGeoTree();

		//新增接口
		void highLightGeometrySetSig(Geometry::GeometrySet *, bool);		//高亮显示主体
		void highLightGeometryPointSig(Geometry::GeometrySet *, int, bool); //高亮显示点
		void highLightGeometryEdgeSig(Geometry::GeometrySet *, int, bool);	//高亮显示边
		void highLightGeometryFaceSig(Geometry::GeometrySet *, int, bool);	//高亮显示面
		void highLightGeometrySolidSig(Geometry::GeometrySet *, int, bool); //高亮显示实体
		void clearGeometryHighLightSig();									//清空所有高亮对象

	protected:
		/**
		 * @brief 翻译对话框文本
		 * @param b 对话框按钮
		 * @since 2.5.0
		 */
		void translateButtonBox(QDialogButtonBox *b);

	private slots:
		// delete***********
		virtual void selectActorShape(vtkActor *, int, Geometry::GeometrySet *);
		/**
		 * @brief 前处理窗口选中几何形状的响应槽函数
		 * @param set 选中的几何几何形状
		 * @param index
		 * @since 2.5.0
		 */
		virtual void shapeSlected(Geometry::GeometrySet *set, int index);

	protected:
		/**
		 * @brief 几何数据
		 * @since 2.5.0
		 */
		Geometry::GeometryData *_geoData{};
		/**
		 * @brief 前处理窗口
		 * @since 2.5.0
		 */
		MainWidget::PreWindow *_preWindow{};

		/**
		 * @brief 是否为编辑模式
		 * @since 2.5.0
		 */
		bool _isEdit{false};

		Geometry::GeometrySet *_editSet{};

		Py::PythonAgent *_pyAgent{};

		bool _restoreSelectMode{true};
	};
}

#endif