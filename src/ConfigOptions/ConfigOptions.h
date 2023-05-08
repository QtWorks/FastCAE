/**
 * @file ConfigOptions.h
 * @brief 可视化定制配置信息读取单例类
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
#ifndef _CONFIGOPTIONS_H_
#define _CONFIGOPTIONS_H_

#include "ConfigDataBase.h"

namespace ConfigOption
{
	/**
	 * @brief 可视化定制配置信息读取单例类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI ConfigOption : public ConfigDataBase
	{
	public:
		static ConfigOption *getInstance();

		bool isGeometryEnabled();
		bool isMeshEnabled();
		bool isPostEnabled();

		BCConfig *getBCConfig() override;
		DataConfig *getDataConfig() override;
		GeometryConfig *getGeometryConfig() override;
		GlobalConfig *getGlobalConfig() override;
		MeshConfig *getMeshConfig() override;
		PostConfig *getPostConfig() override;
		SolverOption *getSolverOption() override;
		ObserverConfig *getObseverConfig() override;
		MaterialConfig *getMaterialConfig() override;
		ProjectTreeConfig *getProjectTreeConfig() override;
		//		NodeFormConfig* getNodeFormConfig()override;

		void clearAllConfig() override;
		//		QString readConfig();

	private:
		ConfigOption();
		~ConfigOption();

	private:
		static ConfigOption *_instance;
		/**
		 * @brief 边界配置（BCConfig.config）
		 * @since 2.5.0
		 */
		BCConfig *_bcConfig{};
		/**
		 * @brief 算例数据配置（DataConfig.config）
		 * @since 2.5.0
		 */
		DataConfig *_dataConfig{};
		/**
		 * @brief 全局配置（GlobalConfig.config）
		 * @since 2.5.0
		 */
		GlobalConfig *_globalConfig{};
		/**
		 * @brief 几何配置（GlobalConfig.config）
		 * @since 2.5.0
		 */
		GeometryConfig *_geoConfig{};
		/**
		 * @brief 网格配置（GlobalConfig.config）
		 * @since 2.5.0
		 */
		MeshConfig *_meshConfig{};
		/**
		 * @brief 后处理配置（GlobalConfig.config）
		 * @since 2.5.0
		 */
		PostConfig *_postConfig{};
		/**
		 * @brief 求解器配置（SolverConfig.config）
		 * @since 2.5.0
		 */
		SolverOption *_solverOption{};
		ObserverConfig *_observerConfig{};
		/**
		 * @brief 材料配置（MaterialConfig.config）
		 * @since 2.5.0
		 */
		MaterialConfig *_materialConfig{};
		/**
		 * @brief 工程树配置（treeConfig.config）
		 * @since 2.5.0
		 */
		ProjectTreeConfig *_projectTreeConfig{};
		//		NodeFormConfig* _nodeFormConfig{};
	};

}

#endif