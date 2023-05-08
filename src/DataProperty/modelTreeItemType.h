/**
 * @file modelTreeItemType.h
 * @brief 模型树相关的一些信息定义
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 09:20
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
#ifndef _MODELTREEITEMTYPE_H_
#define _MODELTREEITEMTYPE_H_

#include <QString>
#include "DataPropertyAPI.h"

/**
 * @brief 模型树类型
 * @since 2.5.0
 */
enum ProjectTreeType
{
	UnDefined = -1,			   ///< 未定义的
	TreeType = 0,			   ///< 树类型
	PluginDefType = 100,	   ///< 插件
	TreeTypeBoundary = 100000, ///< 边界
};

/**
 * @brief 属性菜单项的类型
 * @since 2.5.0
 */
enum TreeItemType
{
	Undefined = -1,					  ///< 未定义的
	GeometryRoot = 1,				  ///< 几何根节点
	GeometryChild,					  ///< 几何子节点
	Datum,							  ///< 基准
	DatumPlane,						  ///< 基准平面
	GeoComponentRoot,				  ///< 几何组件根节点
	GeoComponentChild,				  ///< 几何组件子节点
	MeshRoot,						  ///< 网格根节点
	MeshChild,						  ///< 网格子节点
	MeshSetRoot,					  ///< 网格组件根节点
	MeshSetChild,					  ///< 网格组件子节点
	MaterialRoot,					  ///< 材料根节点
	MaterialChild,					  ///< 材料子节点
	PhyaicsModelRoot,				  ///< 物理模型(算例)根节点
	ProjectRoot,					  ///< 工程根节点（Case_*）
	ProjectSimulationSetting,		  ///< 仿真参数设置
	ProjectSimulationSettingChild,	  ///< 仿真参数设置子节点
	ProjectSimulationSettingGrandSon, ///< 仿真参数设置孙子节点
	ProjectGeometry,				  ///< 几何根节点
	ProjectGeometryChild,			  ///< 几何子节点

	ProjectEleProperty,
	ProjectElePropertyChild,

	ProjectComponent,				  ///< 工程组件节点
	ProjectComponentChild,			  ///< 工程组件子节点
	ProjectBoundaryCondation,		  ///< 工程边界条件节点
	ProjectBoundaryCondationChild,	  ///< 工程边界条件子节点
	ProjectMonitor,					  ///< 监视器节点
	ProjectMonitorChild,			  ///< 监视器子节点
	ProjectSolver,					  ///< 求解设置节点
	ProjectSolverChild,				  ///< 求解设置子节点
	ProjectSolverGrandSon,			  ///< 求解设置孙子节点
	ProjectPostSetting,				  ///< 后处理节点
	ProjectPostSettingChild,		  ///< 后处理子节点
	ProjectCaseTemplate,			  ///<
	ProjectPost,					  ///<
	ProjectPost3DGraph,				  ///< 三维绘图（云图？？？）
	ProjectPost3DGraphChild,		  ///< 三维绘图子节点
	ProJectPost2DGraph,				  ///< 二维绘图
	ProJectPost2DGraphChild,		  ///< 二维绘图子节点
	ProjectPostCounter,				  ///< 云图
	ProjectPostCounterChild,		  ///< 云图子节点
	ProjectPostVector,				  ///< 矢量
	ProjectPostVectorChild,			  ///< 矢量子节点
	ProjectPostStreamLine,			  ///< 流线
	ProjectPostStreamLineChild,		  ///< 流线子节点
	ProjectReport,					  ///< 报告
	ProjectReportChild,				  ///< 报告子节点
	SelfDefineItem,					  ///< 自定义节点
};

extern TreeItemType DATAPROPERTYAPI getTreeItemTypeByString(const QString &type);

extern ProjectTreeType DATAPROPERTYAPI getTreeTypeByString(const QString &type);

extern QString DATAPROPERTYAPI getTreeTypeToString(ProjectTreeType ty);

#endif
