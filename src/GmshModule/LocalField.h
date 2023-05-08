/**
 * @file LocalField.h
 * @brief 局部加密类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-31 18:23
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
#ifndef LOCALFIELD_H
#define LOCALFIELD_H

#include <QString>
#include <QMultiHash>

/**
 * @brief 局部加密类型
 * @since 2.5.0
 */
enum LocalType
{
	UnDefine = 0,  ///< 未定义
	PointSize,	   ///< 点区域网格加密
	BoxField,	   ///< 立方体区域网格加密
	BallField,	   ///< 球体区域网格加密
	CylinderField, ///< 圆柱体区域网格加密
	SolidField,	   ///< 指定实体区域网格加密
	FrustumField,  ///< 锥体区域网格加密
};

namespace Py
{
	class PythonAgent;
}

namespace Gmsh
{
	/**
	 * @brief 局部加密类基类
	 * @since 2.5.0
	 */
	class LocalDensity
	{
	public:
		/**
		 * @brief 提交网格加密相关的python脚本
		 * @param py python交互对象
		 * @since 2.5.0
		 */
		virtual void appendLocals(Py::PythonAgent *py) = 0;
		/**
		 * @brief 获取加密区域信息
		 * @return QStringList 返回加密区域信息
		 * @since 2.5.0
		 */
		virtual QStringList getInformation() = 0;
		/**
		 * @brief 拷贝数据
		 * @param data 要拷贝的源数据
		 * @since 2.5.0
		 */
		virtual void copy(LocalDensity *data);
		/**
		 * @brief 局部加密类型
		 * @since 2.5.0
		 */
		LocalType _type{UnDefine};

		/**
		 * @brief 基点坐标x值
		 * @since 2.5.0
		 */
		double _x{0};
		/**
		 * @brief 基点坐标y值
		 * @since 2.5.0
		 */
		double _y{0};
		/**
		 * @brief 基点坐标z值
		 * @since 2.5.0
		 */
		double _z{0};

		double _thickness{0};
		double _vIn{0};
		double _vOut{0};

		bool _backgroundField{false};
	};

	/**
	 * @brief 点区域加密类
	 * @since 2.5.0
	 */
	class LocalPoint : public LocalDensity
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		LocalPoint() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~LocalPoint() = default;

		void appendLocals(Py::PythonAgent *py) override;
		QStringList getInformation() override;
		void copy(LocalDensity *data) override;

		double _value{0};
	};
	/**
	 * @brief 立方体区域网格加密类
	 * @since 2.5.0
	 */
	class Box : public LocalDensity
	{
	public:
		Box() = default;

		void appendLocals(Py::PythonAgent *py) override;
		QStringList getInformation() override;
		void copy(LocalDensity *data) override;

		double _length{0};
		double _width{0};
		double _height{0};
	};
	/**
	 * @brief 球体区域网格加密类
	 * @since 2.5.0
	 */
	class Ball : public LocalDensity
	{
	public:
		Ball() = default;

		void appendLocals(Py::PythonAgent *py) override;
		QStringList getInformation() override;
		void copy(LocalDensity *data) override;

		double _radius{0};
	};
	/**
	 * @brief 圆柱体区域网格加密类
	 * @since 2.5.0
	 */
	class Cylinder : public LocalDensity
	{
	public:
		void appendLocals(Py::PythonAgent *py) override;
		QStringList getInformation() override;
		void copy(LocalDensity *data) override;

		double _radius{0};
		double _xAxis{0};
		double _yAxis{0};
		double _zAxis{0};
		double _length{0};
	};
	/**
	 * @brief 指定实体模型区域网格加密类
	 * @since 2.5.0
	 */
	class SolidFields : public LocalDensity
	{
	public:
		void appendLocals(Py::PythonAgent *py) override;
		QStringList getInformation() override;
		void copy(LocalDensity *data) override;

		QMultiHash<int, int> _solidHash;
		void setIndex(int d);

	private:
		int _index{0};
	};
	/**
	 * @brief 锥体区域网格加密类
	 * @since 2.5.0
	 */
	class Frustum : public LocalDensity
	{
	public:
		void appendLocals(Py::PythonAgent *py) override;
		QStringList getInformation() override;
		void copy(LocalDensity *data) override;

		double _iRadius{0};
		double _oRadius{0};
		double _iTopRadius{0};
		double _oTopRadius{0};
		double _xAxis{0};
		double _yAxis{0};
		double _zAxis{0};
		double _length{0};
	};
}

#endif // _DEBUG
