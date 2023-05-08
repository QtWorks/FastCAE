/**
 * @file ConfigDataReader.h
 * @brief 定制信息读取类（该类会调用其它reader，算是一个总的reader）
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 14:35
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
#ifndef CONFIGGATAREADER_H_
#define CONFIGGATAREADER_H_

#include "ConfigOptionsAPI.h"
#include <QString>

namespace ConfigOption
{
	class ConfigDataBase;
	/**
	 * @brief 定制信息读取类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI ConfigDataReader
	{
	public:
		ConfigDataReader(QString path, ConfigDataBase *data);
		~ConfigDataReader() = default;

		QString read();

	private:
		QString _path{};
		ConfigDataBase *_data{};
	};

}

#endif // !CONFIGGATAREADER_H_
