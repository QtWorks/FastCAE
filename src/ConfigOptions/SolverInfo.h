/**
 * @file SolverInfo.h
 * @brief 求解器信息类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 15:42
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
#ifndef _SOLVERINFO_H_
#define _SOLVERINFO_H_

#include "ConfigOptionsAPI.h"
#include <QString>
#include <QStringList>

class QDomElement;
class QDomDocument;

namespace ConfigOption
{
	/**
	 * @brief 求解器类型枚举值
	 * @since 2.5.0
	 */
	enum SolverType
	{
		None, ///< 未定义
		SelfDevelop, ///< 自研求解器
		ThirdParty, ///< 第三方求解器
	};
	/**
	 * @brief 求解器信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI SolverInfo
	{
	public:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		SolverInfo() = default;
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~SolverInfo() = default;
		/**
		 * @brief 设置求解器的类型值
		 * @param t 求解器的类型值
		 * @since 2.5.0
		 */
		void setType(SolverType t);
		/**
		 * @brief 获取求解器的类型值
		 * @return SolverType 求解器的类型值
		 * @since 2.5.0
		 */
		SolverType getType();
		/**
		 * @brief 设置求解器的名称
		 * @param n 求解器的名称
		 * @since 2.5.0
		 */
		void setName(QString n);
		/**
		 * @brief 获取求解器的名称
		 * @return QString 求解器的名称
		 * @since 2.5.0
		 */
		QString getName();
		/**
		 * @brief 设置求解器执行文件的路径
		 * @param path 求解器执行文件的路径
		 * @since 2.5.0
		 */
		void setEXEPath(QString path);
		/**
		 * @brief 获取求解器执行文件的路径
		 * @return QString 求解器执行文件的路径
		 * @since 2.5.0
		 */
		QString getExePath();
		/**
		 * @brief 设置求解器的启动参数
		 * @param p 求解器的启动参数
		 * @since 2.5.0
		 */
		void setParameter(QString p);
		/**
		 * @brief 获取求解器的启动参数
		 * @return QString 求解器的启动参数
		 * @since 2.5.0
		 */
		QString getParameter();
		/**
		 * @brief 设置求解器的进度关键字
		 * @param p 求解器的进度关键字
		 * @since 2.5.0
		 */
		void setProcessKeyWord(QString p);
		/**
		 * @brief 获取求解器的进度关键字
		 * @return QString 求解器的进度关键字
		 * @since 2.5.0
		 */
		QString getProcessKeyWord();
		/**
		 * @brief 设置求解器的模板文件
		 * @param tem 求解器的模板文件路径
		 * @since 2.5.0
		 */
		void setTemplate(QString tem);
		/**
		 * @brief 获取求解器的模板文件
		 * @return QString 求解器的模板文件的路径
		 * @since 2.5.0
		 */
		QString getTemplate();
		/**
		 * @brief 设置求解器输入文件的格式
		 * @param f 求解器输入文件的格式
		 * @since 2.5.0
		 */
		void setInputFormat(QString f);
		/**
		 * @brief 获取求解器输入文件的格式
		 * @return QString 求解器输入文件的格式
		 * @since 2.5.0
		 */
		QString getInputFormat();
		/**
		 * @brief 设置求解器输出文件的转换器
		 * @param t 求解器输出文件的转换器
		 * @since 2.5.0
		 */
		void setTransfer(QString t);
		/**
		 * @brief 获取求解器输出文件的转换器
		 * @return QString 求解器输出文件的转换器
		 * @since 2.5.0
		 */
		QString getTransfer();

		bool isWriteTemplate();
		/**
		 * @brief 设置求解器的依赖库文件
		 * @param de 求解器的依赖库文件列表
		 * @since 2.5.0
		 */
		void setDependences(QStringList de);
		/**
		 * @brief 获取求解器的依赖库文件
		 * @return QStringList 求解器的依赖库文件列表
		 * @since 2.5.0
		 */
		QStringList getDependences();


		/**
		 * @brief 读取xml配置文件
		 * @param ele xml配置文件节点对象
		 * @since 2.5.0
		 */
		void readXML(QDomElement *ele);
		/**
		 * @brief 写出xml配置文件
		 * @param doc xml配置文件对象
		 * @param parent xml配置文件父级节点对象
		 * @since 2.5.0
		 */
		void writeXML(QDomDocument* doc, QDomElement *parent);

	private:
		/**
		 * @brief 求解器类型
		 * @enum ConfigOption::SolverType
		 * @since 2.5.0
		 */
		SolverType _type{ None };
		/**
		 * @brief 求解器名称
		 * @since 2.5.0
		 */
		QString _name{};
		/**
		 * @brief 求解器执行文件路径
		 * @since 2.5.0
		 */
		QString _exePath{};
		/**
		 * @brief 求解器的启动参数
		 * @since 2.5.0
		 */
		QString _parameter{};
		/**
		 * @brief 求解器进度关键字
		 * @since 2.5.0
		 */
		QString _process{};
		/**
		 * @brief 求解器输入文件的模板
		 * @since 2.5.0
		 */
		QString _template{};
		/**
		 * @brief 求解器输入文件格式
		 * @since 2.5.0
		 */
		QString _inputFormat{};
		/**
		 * @brief 求解器的转换器
		 * @since 2.5.0
		 */
		QString _transfer{};
		/**
		 * @brief 求解器的依赖库文件
		 * @note 该项仅在可视化定制内可用，用于指定生成安装程序时候要同求解器一起拷贝的依赖库
		 * @since 2.5.0
		 */
		QStringList _dependences{};
	};
}

#endif