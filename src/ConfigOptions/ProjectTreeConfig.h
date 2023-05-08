/**
 * @file ProjectTreeConfig.h
 * @brief 工程树配置信息类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:55
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
#ifndef _PROJECTTREECONFIG_H_
#define _PROJECTTREECONFIG_H_

#include <QMap>
#include <QString>
#include <QStringList>
#include "DataProperty/modelTreeItemType.h"
#include "ConfigOptionsAPI.h"

namespace ConfigOption
{
	class ProjectTreeInfo;
	/**
	 * @brief 工程树配置信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI ProjectTreeConfig
	{
	public:
		ProjectTreeConfig() = default;
		~ProjectTreeConfig();

		void appendTree(ProjectTreeType type, ProjectTreeInfo *ptree);
		ProjectTreeInfo *getProjectTree(ProjectTreeType type);
		QList<ProjectTreeType> getTreeTypes();
		QStringList getTreeNames();
		bool isContains(ProjectTreeType type);
		void clearData();
		QString getNameByType(ProjectTreeType t);
		ProjectTreeType getTypeByName(QString name);

	private:
		QMap<ProjectTreeType, ProjectTreeInfo *> _treeHash{};
	};
}

#endif