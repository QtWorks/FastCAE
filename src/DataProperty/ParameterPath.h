/**
 * @file ParameterPath.h
 * @brief 路径类参数类的头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-09 17:01
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
#ifndef _PARAMETERPATH_H_
#define _PARAMETERPATH_H_

#include "ParameterBase.h"
#include <QString>
#include <QStringList>

namespace DataProperty
{

	/**
	 * @brief 路径类型枚举值
	 * @since 2.5.0
	 */
	enum PathType
	{
		None = 0, ///< 未定义的类别
		Path, ///< 路径
		File, ///< 文件
		FileList, ///< 文件集合

	};
	/**
	 * @brief 路径类参数类
	 * @since 2.5.0
	 */
	class DATAPROPERTYAPI ParameterPath : public ParameterBase
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		ParameterPath();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ParameterPath() = default;
		/**
		 * @brief 从ori中拷贝内容
		 * @param ori 要拷贝内容的源参数对象
		 * @param valueOnly 是否仅仅拷贝值
		 * @since 2.5.0
		 */
		void copy(ParameterBase* ori, bool valueOnly = false) override;
		/**
		 * @brief 设置参数的路径类型（文件、路径、文件集）
		 * @param t 要设置为参数的路径类型
		 * @since 2.5.0
		 */
		void setType(PathType t);
		/**
		 * @brief 获取参数的路径类型
		 * @return PathType 
		 * @since 2.5.0
		 */
		PathType getType();
		/**
		 * @brief 设置参数的后缀
		 * @param s 后缀字符串
		 * @note 仅在参数类型为文件或者文件集时有效
		 * @since 2.5.0
		 */
		void setSuffix(QString s);
		/**
		 * @brief 获取参数的后缀
		 * @return QString 
		 * @since 2.5.0
		 */
		QString getSuffix();
		/**
		 * @brief 设置文件路径
		 * @param f 文件路径
		 * @note 仅在参数类型为文件时有效
		 * @since 2.5.0
		 */
		void setFile(QString f);
		/**
		 * @brief 获取文件路径
		 * @return QString 
		 * @since 2.5.0
		 */
		QString getFile();
		/**
		 * @brief 设置文件列表
		 * @param sl 文件列表
		 * @note 仅在参数类型为文件集合时有效
		 * @since 2.5.0
		 */
		void setFileList(QStringList sl);
		/**
		 * @brief 获取文件列表
		 * @return QStringList 
		 * @since 2.5.0
		 */
		QStringList getFileList();
		/**
		 * @brief 设置路径
		 * @param s 路径
		 * @note 仅在参数类型为路径时有效
		 * @since 2.5.0
		 */
		void setPath(QString s);
		/**
		 * @brief 获取路径
		 * @return QString 
		 * @since 2.5.0
		 */
		QString getPath();
		/**
		 * @brief 将参数对象写入到工程文件
		 * @param doc 工程文件的QDomDocument对象
		 * @param parent 要追加该参数的父节点
		 * @since 2.5.0
		 */
		void writeParameter(QDomDocument* doc, QDomElement* parent) override;
		/**
		 * @brief 从工程文件中对应节点读取参数
		 * @param e 工程文件中对应的节点对象
		 * @since 2.5.0
		 */
		void readParameter(QDomElement* e) override;
		/**
		 * @brief 将参数转换为字符串类型（QString）值
		 * @return QString 转换后得到的字符串值
		 * @since 2.5.0
		 */
		QString valueToString() override;
		/**
		 * @brief 设置从字符串对象获取参数值（转换）
		 * @param v 要操作的字符串
		 * @since 2.5.0
		 */
		void setValueFromString(QString v) override;

	private:
		/**
		 * @brief 参数类型
		 * @since 2.5.0
		 */
		PathType _type{ None };
		/**
		 * @brief 参数后缀
		 * @since 2.5.0
		 */
		QString _suffix{"All Files(*)"};
		/**
		 * @brief 参数的路径值
		 * @since 2.5.0
		 */
		QString _path{};
		/**
		 * @brief 参数的文件路径值
		 * @since 2.5.0
		 */
		QString _file{};
		/**
		 * @brief 参数的文件路径集合
		 * @since 2.5.0
		 */
		QStringList _files{};
	};

}


#endif