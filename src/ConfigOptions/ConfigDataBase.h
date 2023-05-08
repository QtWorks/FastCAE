/**
 * @file ConfigDataBase.h
 * @brief 可视化定制信息基类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:27
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
#ifndef CONFIGDATABASE_H
#define CONFIGDATABASE_H

#include "ConfigOptionsAPI.h"

namespace ConfigOption
{
	class BCConfig;
	class DataConfig;
	class GlobalConfig;
	class GeometryConfig;
	class MeshConfig;
	class PostConfig;
	class SolverOption;
	class ObserverConfig;
	class MaterialConfig;
	class ProjectTreeConfig;
	//	class NodeFormConfig;

	class CONFIGOPTIONSAPI ConfigDataBase
	{
	public:
		ConfigDataBase() = default;
		~ConfigDataBase() = default;

		virtual BCConfig *getBCConfig() = 0;
		virtual DataConfig *getDataConfig() = 0;
		virtual GeometryConfig *getGeometryConfig() = 0;
		virtual GlobalConfig *getGlobalConfig() = 0;
		virtual MeshConfig *getMeshConfig() = 0;
		virtual PostConfig *getPostConfig() = 0;
		virtual SolverOption *getSolverOption() = 0;
		virtual ObserverConfig *getObseverConfig() = 0;
		virtual MaterialConfig *getMaterialConfig() = 0;
		virtual ProjectTreeConfig *getProjectTreeConfig() = 0;
		//		virtual NodeFormConfig* getNodeFormConfig() = 0;

		virtual void clearAllConfig() = 0;
	};

}

#endif