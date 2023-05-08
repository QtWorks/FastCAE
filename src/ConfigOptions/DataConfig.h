/**
 * @file DataConfig.h
 * @brief 算例数据配置类（包括跟特定算例相关的信息）
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:36
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
#ifndef _DATACONFIG_H_
#define _DATACONFIG_H_

#include "ConfigOptionsAPI.h"
#include "DataProperty/DataBase.h"
#include "DataProperty/modelTreeItemType.h"
#include <QHash>

namespace DataProperty
{
	class DataBase;
}

namespace ConfigOption
{
	class PostCurve;
	/**
	 * @brief 算例数据配置类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI DataConfig
	{
	public:
		DataConfig() = default;
		~DataConfig();

		void appendSimlutationData(ProjectTreeType t, DataProperty::DataBase *data);
		DataProperty::DataBase *getSimlutationData(ProjectTreeType t);

		void appendSolverSettingData(ProjectTreeType t, DataProperty::DataBase *data);
		DataProperty::DataBase *getSolverSettingData(ProjectTreeType t);
		void appendConfigData(ProjectTreeType type, const int id, DataProperty::DataBase *d);
		DataProperty::DataBase *getConfigData(ProjectTreeType type, int id);
		QHash<int, DataProperty::DataBase *> getConfigData(ProjectTreeType t);

		//		void appendMonitorFile(ProjectTreeType type);
		QStringList getMonitorFile(ProjectTreeType type);
		void appendMonitorCurves(ProjectTreeType type, PostCurve *curves);
		QList<PostCurve *> getMonitorCurves(ProjectTreeType type);

		void clearData();

	private:
		QHash<ProjectTreeType, DataProperty::DataBase *> _simlutationDataHash{};
		QHash<ProjectTreeType, DataProperty::DataBase *> _solverSettingHash{};
		QHash<ProjectTreeType, QHash<int, DataProperty::DataBase *>> _configData{};
		//		QHash<ProjectTreeType, q> _monitorFile{};
		QHash<ProjectTreeType, QList<PostCurve *>> _monitorCurves{};
	};
}

#endif