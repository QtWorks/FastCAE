/**
 * @file MaterialConfig.h
 * @brief 材料配置信息类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:45
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
#ifndef _MATERIALCONFIG_H
#define _MATERIALCONFIG_H_

#include "ConfigOptionsAPI.h"
#include <QHash>
#include <QStringList>

namespace Material
{
	class Material;
}

namespace ConfigOption
{
	/**
	 * @brief 材料配置信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI MaterialConfig
	{
	public:
		MaterialConfig() = default;
		~MaterialConfig();

		QStringList getMaterialTypes();
		Material::Material *getMaterialByType(QString t);
		void clearData();

		bool readConfig(QString file);

	private:
		QHash<QString, Material::Material *> _materialHash{};
	};

}

#endif