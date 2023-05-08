/**
 * @file TreeConfigReader.h
 * @brief 模型树配置信息读取类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:58
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
#ifndef TREECONFIGREADER_H
#define TREECONFIGREADER_H

#include <QString>
#include "ConfigOptionsAPI.h"
#include <QFile>
//#include "ModuleBase/IOBase.h"

class QDomDocument;
class QDomElement;

namespace ConfigOption
{
	class ProjectTreeConfig;
	class ProjectTreeInfo;
	/**
	 * @brief 模型树配置信息读取类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI TreeConfigReader /*: public ModuleBase::IOBase*/
	{
	public:
		TreeConfigReader(const QString &fileName, ProjectTreeConfig *treeconfig);
		~TreeConfigReader();
		bool read();

	private:
		void readTree(QDomElement *);
		void readChildNode(ProjectTreeInfo *tree, QDomElement *ele);

	private:
		ProjectTreeConfig *_info{};
		QDomDocument *_doc{};
		QFile _file{};
	};

}

#endif