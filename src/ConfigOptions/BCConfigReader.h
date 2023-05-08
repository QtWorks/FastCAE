/**
 * @file BCConfigReader.h
 * @brief 边界条件配置读取类，用于读取可视化定制生成的BCConfig.config文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:23
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
#ifndef _BCCONFIGREADER_H_
#define _BCCONFIGREADER_H_

#include <QFile>
#include <QString>
//#include "ModuleBase/IOBase.h"
#include "DataProperty/modelTreeItemType.h"

class QDomDocument;
class QDomElement;

namespace ConfigOption
{
	class BCConfig;

	/**
	 * @brief 边界条件读取类
	 * @since 2.5.0
	 */
	class BCConfigReader //: public ModuleBase::IOBase
	{
	public:
		BCConfigReader(const QString fileName, BCConfig *bcconfig);
		~BCConfigReader();

		bool read() /* override*/;

	private:
		void readBCType(QDomElement *ele, ProjectTreeType t);
		void readBC(QDomElement *ele, ProjectTreeType t);

	private:
		/**
		 * @brief 边界条件配置
		 * @since 2.5.0
		 */
		BCConfig *_bcconfig{};
		/**
		 * @brief xml文件对象（QDomDocument）
		 * @since 2.5.0
		 */
		QDomDocument *_doc{};
		/**
		 * @brief 要读取的文件（BCConfig.config）
		 * @since 2.5.0
		 */
		QFile _file;
	};

}

#endif