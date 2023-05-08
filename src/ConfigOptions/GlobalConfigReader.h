/**
 * @file GlobalConfigReader.h
 * @brief 全局配置信息读取类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:42
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
#include "ModuleBase/IOBase.h"
#include <QString>
#include <QFile>

class QDomElement;
class QDomDocument;

namespace ConfigOption
{
	class GeometryConfig;
	class GlobalConfig;
	class MeshConfig;
	class PostConfig;
	class ConfigDataBase;
	/**
	 * @brief 全局配置信息读取类
	 * @since 2.5.0
	 */
	class GlobalConfigReader
	{
	public:
		GlobalConfigReader(QString fileName, ConfigDataBase *data);
		~GlobalConfigReader();

		bool read();

	private:
		bool readGlobal(QDomElement *e);
		bool readGeometry(QDomElement *e);
		bool readMesh(QDomElement *e);
		bool readPost(QDomElement *e);

	private:
		GlobalConfig *_globalConfig{};
		GeometryConfig *_geoConfig{};
		MeshConfig *_meshConfig{};
		PostConfig *_postConfig{};

		QFile _file{};
		QDomDocument *_doc{};
	};

}