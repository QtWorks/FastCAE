/**
 * @file GeoCommandBase.h
 * @brief 几何命令基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 16:19
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
#ifndef GEOCOMMANDBASE_H_
#define GEOCOMMANDBASE_H_

#ifndef PI
#define PI 3.14159265358979323846
#endif

#include <QObject>
#include "geometryCommandAPI.h"
#include <QList>

namespace DataProperty
{
	class DataBase;
}

namespace GUI
{
	class MainWindow;
}

namespace MainWidget
{
	class PreWindow;
}

namespace Geometry
{
	class GeometryData;
	class GeometrySet;
	class GeometryDatum;
}

class TopoDS_Shape;

namespace Command
{
	/**
	 * @brief 命令类型枚举值
	 * @since 2.5.0
	 */
	enum CommandType
	{
		D3Feature, ///< 三维特征
		Sketch,	   ///< 草绘特征
	};

	class GeoComandList;

	/**
	 * @brief 几何命令基类
	 * @since 2.5.0
	 */
	class GEOMETRYCOMMANDAPI GeoCommandBase : public QObject
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param m 主窗口对象
		 * @param p 前处理窗口对象
		 * @since 2.5.0
		 */
		GeoCommandBase(GUI::MainWindow *m, MainWidget::PreWindow *p);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeoCommandBase() = default;
		/**
		 * @brief 命令执行调用的函数
		 * @return bool 返回执行结果
		 * @since 2.5.0
		 */
		virtual bool execute() = 0;
		/**
		 * @brief 撤销操作
		 * @since 2.5.0
		 */
		virtual void undo();
		/**
		 * @brief 重做操作
		 * @since 2.5.0
		 */
		virtual void redo();
		virtual void releaseResult();
		/**
		 * @brief 获取命令执行后的结果形状
		 * @return TopoDS_Shape* 返回结果形状
		 * @since 2.5.0
		 */
		TopoDS_Shape *getResultShape();
		/**
		 * @brief 获取命令类型
		 * @return CommandType 返回命令类型
		 * @since 2.5.0
		 */
		CommandType getComamndType();
		void setEditData(Geometry::GeometrySet *set);

	signals:
		void updateGeoTree();
		void showSet(Geometry::GeometrySet *s, bool r = true);
		void showDatum(Geometry::GeometryDatum *);
		void removeDisplayActor(Geometry::GeometrySet *s);
		void removeDisplayDatumActor(Geometry::GeometryDatum *);
		/**
		 * @brief 命令执行后会触发此信号
		 * @since 2.5.0
		 */
		void updateActions();
		/**
		 * @brief 执行撤销操作后会触发此信号
		 * @param data
		 * @since 2.5.0
		 */
		void updatePropertySig(DataProperty::DataBase *data);

	protected:
		/**
		 * @brief 主窗口对象
		 * @since 2.5.0
		 */
		GUI::MainWindow *_mainWindow{};
		/**
		 * @brief 前处理窗口对象
		 * @since 2.5.0
		 */
		MainWidget::PreWindow *_preWindow{};
		/**
		 * @brief 命令类型
		 * @since 2.5.0
		 */
		CommandType _type{D3Feature};
		/**
		 * @brief 命令执行后的形状
		 * @since 2.5.0
		 */
		TopoDS_Shape *_resShape{};

		Geometry::GeometryData *_geoData{};
		/**
		 * @brief 命令列表
		 * @since 2.5.0
		 */
		GeoComandList *_commandList{};

		bool _isEdit{false};
		Geometry::GeometrySet *_editSet{};
	};
}

#endif