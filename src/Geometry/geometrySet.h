/**
 * @file geometrySet.h
 * @brief 几何形状表示类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-24 11:03
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
#ifndef GEOMETRYSET_H
#define GEOMETRYSET_H

#include "geometryAPI.h"
#include "DataProperty/DataBase.h"
#include <QString>
//#include <TopoDS_Shape.hxx>
//#include <vtkSmartPointer.h>

class TopoDS_Shape;
class vtkDataSet;
class vtkPolyData;

namespace Geometry
{
	/**
	 * @brief 几何
	 * @since 2.5.0
	 */
	enum GeometryType
	{
		NONE = 0,
		IGES,
		STEP,
		STL,
		DATUM,
	};

	class GeometryModelParaBase;

	/**
	 * @brief 几何形状类
	 * @note 用来表示一个具体的形状，可以是一个点、一个曲面、一个实体，也可以表示上述元素组成的复杂几何形状
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeometrySet : public DataProperty::DataBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @param type
		 * @param needID
		 * @since 2.5.0
		 */
		GeometrySet(GeometryType type = NONE, bool needID = true);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometrySet();
		/**
		 * @brief 删除全部子形状并释放子形状内存
		 * @since 2.5.0
		 */
		void releaseSubSet();
		void setID(int id) override;
		/**
		 * @brief 重置最大ID
		 * @attention 不要轻易调用
		 * @since 2.5.0
		 */
		static void resetMaxID();
		/**
		 * @brief 根据ID获取子形状
		 * @param id 要获取ID的子形状
		 * @return GeometrySet* 返回的子形状
		 * @since 2.5.0
		 */
		GeometrySet *getSetByID(int id);
		// 		int getID();
		// 		void setName(const QString& name);
		// 		QString getName();
		// 		void setFilePath(const QString& filepath);
		// 		QString getFilePath();

		/**
		 * @brief 获取形状的数量
		 * @param type 形状类别（1-点 2-线 3-面 4-实体）
		 * @return int 返回指定形状的数量，错误时返回-1
		 * @since 2.5.0
		 */
		int getGeoMemberCount(int type);
		/**
		 * @brief 获取形状
		 * @param type 形状类别（1-点 2-线 3-面 4-实体）
		 * @param index 形状的索引值
		 * @return TopoDS_Shape* 返回形状对象
		 * @since 2.5.0
		 */
		TopoDS_Shape *getShape(int type, int index);
		/**
		 * @brief 获取形状
		 * @param type 形状类别（1-点 2-线 3-面 4-实体）
		 * @param index 形状的索引值
		 * @return TopoDS_Shape* 返回形状对象
		 * @since 2.5.0
		 */
		const TopoDS_Shape &getRealShape(int type, int index);
		/**
		 * @brief 设置可见性
		 * @param v 是否可见
		 * @since 2.5.0
		 */
		void setVisible(bool v);
		/**
		 * @brief 判断是否可见
		 * @return bool 返回可见性
		 * @since 2.5.0
		 */
		bool isVisible();
		/**
		 * @brief 设置类型
		 * @param type 要设置的类型
		 * @since 2.5.0
		 */
		void setType(GeometryType type);
		/**
		 * @brief 获取类型
		 * @return GeometryType 返回的类型
		 * @since 2.5.0
		 */
		GeometryType getType();
		/**
		 * @brief 设置形状的拓扑
		 * @param shape 要设置的拓扑
		 * @since 2.5.0
		 */
		void setShape(TopoDS_Shape *shape);
		/**
		 * @brief 获取形状的拓扑
		 * @return TopoDS_Shape* 返回的拓扑
		 * @since 2.5.0
		 */
		TopoDS_Shape *getShape();

		void setPoly(vtkPolyData* poly);
		vtkPolyData* getPoly();
		// 		void setStlDataSet(vtkSmartPointer<vtkDataSet> polyData);
		// 		vtkDataSet* getStlDataSet();
		/**
		 * @brief 获取最大的ID值
		 * @return int 返回最大ID值
		 * @since 2.5.0
		 */
		static int getMaxID();
		/**
		 * @brief 设置操作参数
		 * @param p 要设置的操作参数
		 * @since 2.5.0
		 */
		void setParameter(GeometryModelParaBase *p);
		/**
		 * @brief 获取操作参数
		 * @return GeometryModelParaBase* 返回操作参数
		 * @since 2.5.0
		 */
		GeometryModelParaBase *getParameter();
		/**
		 * @brief 是否可以编辑
		 * @return bool 返回是否可编辑
		 * @since 2.5.0
		 */
		bool isEditable();
		/**
		 * @brief 移除子形状
		 * @param set 要移除的子形状
		 * @since 2.5.0
		 */
		void removeSubSet(GeometrySet *set);
		/**
		 * @brief 添加子形状
		 * @param set 要添加的子形状
		 * @since 2.5.0
		 */
		void appendSubSet(GeometrySet *set);
		/**
		 * @brief 获取子形状的数量
		 * @return int 返回子形状的数量
		 * @since 2.5.0
		 */
		int getSubSetCount();
		/**
		 * @brief 获取索引为index的子形状
		 * @param index 要获取子形状的索引
		 * @return GeometrySet* 返回子形状
		 * @since 2.5.0
		 */
		GeometrySet *getSubSetAt(int index);

		void dataToStream(QDataStream *s) override;
		virtual QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *ele, bool isDisp = false);
		virtual void readDataFromProjectFile(QDomElement *e, bool isDiso = false);
		/**
		 * @brief 写出brep文件
		 * @param name 要写出的brep文件
		 * @return bool 返回写出结果
		 * @since 2.5.0
		 */
		bool writeBrep(QString name);

		bool writePoly(QString name);
		/**
		 * @brief 读入brep文件
		 * @param name 要读取的brep文件
		 * @attention 路径不能出现中文
		 * @return bool 返回读取结果
		 * @since 2.5.0
		 */
		bool readBrep(QString name);

		bool readPoly(QString name);

	protected:
		void writeSubSet(QDomDocument *doc, QDomElement *parent, bool isDiso = false);
		void readSubSet(QDomElement *e, bool isDiso = false);

	protected:
		//		int _id{ -1 };
		//		QString _name{};
		//		QString _filePath{};
		vtkPolyData* _polyData{};
		/**
		 * @brief
		 * @since 2.5.0
		 */
		GeometryType _type{NONE};
		/**
		 * @brief 是否可见
		 * @since 2.5.0
		 */
		bool _visible{true};
		/**
		 * @brief 对象所表示的TopoDS_Shape对象
		 * @since 2.5.0
		 */
		TopoDS_Shape *_shape{};
		/**
		 * @brief 子形状列表
		 * @since 2.5.0
		 */
		QList<GeometrySet *> _subSetList{};
		/**
		 * @brief 操作参数类对象
		 * @since 2.5.0
		 */
		GeometryModelParaBase *_parameter{};

	private:
		static int idOffset;
		static TopoDS_Shape *tempShape;
	};
}

#endif
