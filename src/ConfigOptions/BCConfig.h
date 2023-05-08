/**
 * @file BCConfig.h
 * @brief 边界条件设置选项（为可视化定制提供接口）
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:06
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
#ifndef _BCCONFIG_H_
#define _BCCONFIG_H_

#include "ConfigOptionsAPI.h"
#include <QStringList>
#include <QString>
#include <QList>
#include "DataProperty/modelTreeItemType.h"
#include <QHash>

namespace BCBase
{
	class BCUserDef;
}

namespace ConfigOption
{
	/**
	 * @brief 边界条件设置选项
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI BCConfig
	{
	public:
		BCConfig() = default;
		~BCConfig();

		void clearData();

		BCBase::BCUserDef *getBCByName(QString name, ProjectTreeType t);
		void appendBC(BCBase::BCUserDef *bc, ProjectTreeType t);
		int getBCCount(ProjectTreeType t);
		BCBase::BCUserDef *getBCAt(const int index, ProjectTreeType t);
		void appendEnableType(QString t, ProjectTreeType type);
		bool isEnable(QString type, ProjectTreeType t);
		QStringList getEnabledType(ProjectTreeType t);

	private:
		QHash<ProjectTreeType, QList<BCBase::BCUserDef *>> _bcList{};
		/**
		 * @brief 可用的边界列表（通过定制功能实现变更）
		 * @since 2.5.0
		 */
		QHash<ProjectTreeType, QStringList> _enableType{};
	};

}

#endif