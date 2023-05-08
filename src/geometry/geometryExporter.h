/**
 * @file geometryExporter.h
 * @brief 几何导出类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 15:33
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
#ifndef GEOMETRYEXPORTER_H_
#define GEOMETRYEXPORTER_H_

#include "geometryAPI.h"
#include <QString>

namespace Geometry
{
	class GeometryData;

	/**
	 * @brief 几何导出类
	 * @since 2.5.0
	 */
	class GEOMETRYAPI GeometryExporter
	{
	public:
		/**
		 * @brief 构造函数
		 * @param fileName 导出文件名
		 * @since 2.5.0
		 */
		GeometryExporter(QString fileName);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GeometryExporter() = default;
		/**
		 * @brief 写出几何文件
		 * @return bool 返回写出结果
		 * @since 2.5.0
		 */
		bool write();

	private:
		/**
		 * @brief 写出brep格式文件
		 * @param file 要写出文件的路径
		 * @return bool 返回写出结果
		 * @since 2.5.0
		 */
		bool writeBrep(const char *file);
		/**
		 * @brief 写出igs格式文件
		 * @param file 要写出文件的路径
		 * @return bool 返回写出结果
		 * @since 2.5.0
		 */
		bool writeIgs(const char *file);
		/**
		 * @brief 写出stp格式文件
		 * @param file 要写出文件的路径
		 * @return bool 返回写出结果
		 * @since 2.5.0
		 */
		bool writeStp(const char *file);

	private:
		/**
		 * @brief 写出文件的路径
		 * @since 2.5.0
		 */
		QString _fileName{};
		/**
		 * @brief 要导出的几何数据
		 * @since 2.5.0
		 */
		GeometryData *_geoData{};
	};
}

#endif