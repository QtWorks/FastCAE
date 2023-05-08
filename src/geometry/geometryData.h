/**
 * @file geometryData.h
 * @brief 几何数据管理基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-24 10:51
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
#ifndef GEOMETRYDATA_H
#define GEOMETRYDATA_H

#include "geometryAPI.h"
#include <QString>
#include <QList>
#include <QStringList>
#include "DataProperty/DataBase.h"

class TopoDS_Shape;
class QDomDocument;
class QDomElement;
class QDomNodeList;
class gp_Ax3;
class vtkPolyData;

namespace Geometry
{
	class GeometrySet;
	class GeometryDatum;
	class GeoComponent;
	/**
	 * @brief 几何数据管理基类（单例）
	 * @note 管理几何相关操作生成的GeometrySet类对象
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeometryData : public DataProperty::DataBase
	{
	public:
		/**
		 * @brief 获取单例指针
		 * @return GeometryData* 返回单例指针
		 * @since 2.5.0
		 */
		static GeometryData *getInstance();
		/**
		 * @brief 添加形状
		 * @param set 要添加的形状
		 * @since 2.5.0
		 */
		void appendGeometrySet(GeometrySet *set);
		/**
		 * @brief 添加基准
		 * @param datum 要添加的基准
		 * @since 2.5.0
		 */
		void appendGeometryDatum(GeometryDatum *datum);
		/**
		 * @brief 获取全部基准
		 * @return QList<GeometryDatum*> 返回的基准列表
		 * @since 2.5.0
		 */
		QList<GeometryDatum *> getGeometryDatum();
		/**
		 * @brief 获取形状的数量
		 * @return int 返回形状的数量
		 * @since 2.5.0
		 */
		int getGeometrySetCount();
		/**
		 * @brief 判断几何数据是否包含形状
		 * @return bool
		 * @since 2.5.0
		 */
		bool isEmpty();
		/**
		 * @brief 获取索引为index的形状
		 * @param index 要获取形状的索引
		 * @return GeometrySet* 返回获取的形状
		 * @attention 索引越界的时候返回nullptr
		 * @since 2.5.0
		 */
		GeometrySet *getGeometrySetAt(const int index);
		/**
		 * @brief 获取获取形状对应的索引
		 * @param s 指定的形状
		 * @return int 返回指定性转的索引
		 * @attention 获取失败时返回-1
		 * @since 2.5.0
		 */
		int getIndexByGeoometrySet(GeometrySet *s);
		/**
		 * @brief 移除索引值为index的形状
		 * @param index 要移除形状的索引
		 * @since 2.5.0
		 */
		void removeGeometrySet(const int index);
		/**
		 * @brief 替换形状
		 * @param newset 替换后的形状
		 * @param oldset 替换前的形状
		 * @attention 如果oldset不是当前对象的形状，则不会执行替换操作
		 * @since 2.5.0
		 */
		void replaceSet(GeometrySet *newset, GeometrySet *oldset);
		/**
		 * @brief 移除直接子形状
		 * @param set 要移除的直接子形状
		 * @note 该函数执行移除操作时不会递归移除
		 * @since 2.5.0
		 */
		void removeTopGeometrySet(GeometrySet *set);
		/**
		 * @brief 判断是否存在直接子形状
		 * @param set 要判断的直接子形状
		 * @return bool 返回是否存在直接子形状
		 * @since 2.5.0
		 */
		bool hasGeometrySet(GeometrySet *set);
		//		void removeDatumPlaneByIndex(int index);
		/**
		 * @brief 移除直接子基准
		 * @param datum 要移除的直接子形状
		 * @since 2.5.0
		 */
		void removeGeometryDatum(GeometryDatum *datum);
		/**
		 * @brief 设置几何形状的可见性
		 * @param index 要设置形状的索引
		 * @param visable 要设置的可见性
		 * @since 2.5.0
		 */
		void setVisable(int index, bool visable);
		/**
		 * @brief 清空所有内容
		 * @since 2.5.0
		 */
		void clear();
		/**
		 * @brief 根据ID获取几何形状
		 * @param id 要获取形状的ID
		 * @return GeometrySet* 返回获取到的几何形状
		 * @attention 如果ID值不合法，则返回nullptr
		 * @since 2.5.0
		 */
		GeometrySet *getGeometrySetByID(const int id);
		/**
		 * @brief 获取索引为index的基准
		 * @param index 要获取基准的索引值
		 * @return GeometryDatum* 返回获取到的基准
		 * @since 2.5.0
		 */
		GeometryDatum *getDatumByIndex(const int index);
		/**
		 * @brief 获取对象的md5值
		 * @return QString 返回计算得到的md5值
		 * @since 2.5.0
		 */
		QString getMD5();
		/**
		 * @brief 根据ID值进行内部排序
		 * @since 2.5.0
		 */
		void sort();
		///文件写出至工程文件
		QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *element, bool isdiso = false);
		//从工程文件读入数据
		void readFromProjectFile(QDomNodeList *nodelist, bool isdiso = false);
		/**
		 * @brief 设置草绘平面
		 * @param loc 草绘平面的坐标原点
		 * @param dir 草绘平面的方向向量
		 * @since 2.5.0
		 */
		void setSketchPlane(double *loc, double *dir);
		/**
		 * @brief 获取草绘平面
		 * @return gp_Ax3* 返回草绘平面
		 * @since 2.5.0
		 */
		gp_Ax3 *getSketchPlane();
		/**
		 * @brief 添加几何组件
		 * @since 2.5.0
		 */
		void appendGeoComponent(GeoComponent *);
		/**
		 * @brief 获取所有的几何组件
		 * @return QList<GeoComponent *>& 返回所有的几何组件
		 * @since 2.5.0
		 */
		QList<GeoComponent *> &getGeoComponentList();
		/**
		 * @brief 根据索引获取组件
		 * @return GeoComponent* 返回组件
		 * @since 2.5.0
		 */
		GeoComponent *getGeoComponentByIndex(int);
		/**
		 * @brief 根据ID获取组件
		 * @return GeoComponent* 返回组件
		 * @since 2.5.0
		 */
		GeoComponent *getGeoComponentByID(int);
		/**
		 * @brief 通过索引删除组件
		 * @return bool 返回删除操作是否执行成功
		 * @since 2.5.0
		 */
		bool removeGeoComponentByIndex(int);
		/**
		 * @brief 删除组件
		 * @return bool 返回删除操作是否执行成功
		 * @since 2.5.0
		 */
		bool removeGeoComponent(GeoComponent *);
		//对所有几何组件进行剖分，然后生成网格并写入XML中
		// void generateMeshAndWriteToXML(QDomDocument& doc, QDomElement& parent);

	private:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		GeometryData() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometryData();

	private:
		/**
		 * @brief 单例指针
		 * @since 2.5.0
		 */
		static GeometryData *_instance;
		/**
		 * @brief 几何形状列表
		 * @since 2.5.0
		 */
		QList<GeometrySet *> _geometryList{};
		/**
		 * @brief 基准列表
		 * @since 2.5.0
		 */
		QList<GeometryDatum *> _geomtretryDatumList{};
		/**
		 * @brief 草绘平面
		 * @since 2.5.0
		 */
		gp_Ax3 *_sketchPlan{};
		/**
		 * @brief 组件列表
		 * @since 2.5.0
		 */
		QList<GeoComponent *> _geoCpList;
		//		QHash<int, vtkPolyData*> _geoCp
	};

	bool compareSet(DataProperty::DataBase *s1, DataProperty::DataBase *s2);
}

#endif