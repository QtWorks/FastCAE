/**
 * @file DataConfigReader.h
 * @brief 算例数据配置信息读取类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:43
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
#ifndef _DATACONFIGREADER_H_
#define _DATACONFIGREADER_H_

#include <QString>
//#include "ModuleBase/IOBase.h"
#include <QFile>
#include "DataProperty/modelTreeItemType.h"

class QDomElement;
class QDomDocument;

namespace ConfigOption
{
	class DataConfig;
	class PostConfig;
	/**
	 * @brief 算例数据配置信息读取类
	 * @since 2.5.0
	 */
	class DataConfigReader //: public ModuleBase::IOBase
	{
	public:
		DataConfigReader(const QString fileName, DataConfig *dataconfig, PostConfig *postconfig);
		~DataConfigReader();

		bool read() /*override*/;

	private:
		void readDataBlock(ProjectTreeType t, QDomElement *e);
		void readPostConfig(ProjectTreeType t, QDomElement *e);

	private:
		DataConfig *_dataConfig{};
		PostConfig *_postConfig{};
		QDomDocument *_doc{};
		QFile _file{};
	};

}

#endif