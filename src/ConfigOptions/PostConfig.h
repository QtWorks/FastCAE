/**
 * @file PostConfig.h
 * @brief 后处理配置信息类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:49
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
#ifndef _POSTCONFIG_H_
#define _POSTCONFIG_H_

#include "ConfigOptionsAPI.h"
#include "DataProperty/modelTreeItemType.h"
#include <QHash>

namespace ConfigOption
{
	class PostConfigInfo;
	/**
	 * @brief 后处理配置信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI PostConfig
	{
	public:
		PostConfig();
		~PostConfig() = default;

		void enablePost(bool on);
		bool isPostEnabled();
		void enablePost2D(bool on);
		bool isPost2DEnabled();
		void enablePost3D(bool on);
		bool isPost3DEnabled();
		void setPostConfigInfo(ProjectTreeType type, PostConfigInfo *info);
		PostConfigInfo *getPostConfigInfo(ProjectTreeType type);
		void clearData();

	private:
		bool _enablePost{false};
		bool _enablePost2D{false};
		bool _enablePost3D{false};

		QHash<ProjectTreeType, PostConfigInfo *> _postConfigInfo{};
		//		QHash<ProjectTreeType, double> _post3DConfig{};
	};

}

#endif
