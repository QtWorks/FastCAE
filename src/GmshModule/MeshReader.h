/**
 * @file MeshReader.h
 * @brief 网格读取类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-04-01 10:21
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
#ifndef MESHREADER_H
#define MESHREADER_H

#include <QString>
#include <QTextStream>
#include <vtkCellType.h>

class vtkUnstructuredGrid;
class vtkDataSet;

namespace MeshData
{
	class MeshData;
	class MeshKernal;
}

namespace Gmsh
{
	/**
	 * @brief 网格读取类头
	 * @since 2.5.0
	 */
	class MeshReader
	{
	public:
		/**
		 * @brief 构造函数
		 * @param file 网格文件路径
		 * @since 2.5.0
		 */
		MeshReader(QString file);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~MeshReader();
		/**
		 * @brief 读取网格文件
		 * @return bool 返回读取结果
		 * @since 2.5.0
		 */
		bool read();

	private:
		/**
		 * @brief 从二进制文件读取一行
		 * @param line
		 * @param b
		 * @since 2.5.0
		 */
		void readLine(QString &line, bool b = false);
		/**
		 * @brief 读取网格节点信息
		 * @param g
		 * @param line
		 * @return bool
		 * @since 2.5.0
		 */
		bool readNodes(vtkUnstructuredGrid *g, QString &line);
		/**
		 * @brief 读取网格单元信息
		 * @param g
		 * @param line
		 * @return bool
		 * @since 2.5.0
		 */
		bool readElements(vtkUnstructuredGrid *g, QString &line);
		bool readNSet(QString &line, MeshData::MeshKernal *k);
		bool readElSet(QString &line, MeshData::MeshKernal *k);
		/**
		 * @brief 获取单元类型
		 * @param s vtk的二进制文件中读取到表示单元类型的字符串
		 * @return VTKCellType 返回VTK预定义的单元类型
		 * @since 2.5.0
		 */
		VTKCellType getVTKCellType(QString s);

		/*bool judgetIndex(int d);*/

	private:
		/**
		 * @brief 网格文件
		 * @since 2.5.0
		 */
		QString _fileName{};
		/**
		 * @brief 二进制数据流
		 * @since 2.5.0
		 */
		QTextStream *_stream{};
		/**
		 * @brief 网格数据
		 * @since 2.5.0
		 */
		MeshData::MeshData *_meshData{};
		/**
		 * @brief 节点索引
		 * @since 2.5.0
		 */
		QHash<int, int> _nodeIDIndex{};
		/**
		 * @brief 单元索引
		 * @since 2.5.0
		 */
		QHash<int, int> _elemIDIndex{};

		int _nIndex{0};
		int _eIndex{0};

		/*QList<int> _indexList{};*/
	};
}

#endif // MESHREADER_H
