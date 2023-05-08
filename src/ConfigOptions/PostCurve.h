/**
 * @file PostCurve.h
 * @brief 二维曲线配置信息类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:54
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
#ifndef _POSTCURVE_H_
#define _POSTCURVE_H_

#include "DataProperty/DataBase.h"
#include "ConfigOptions/ConfigOptionsAPI.h"
#include <QString>

namespace ConfigOption
{
	/**
	 * @brief 二维曲线配置信息类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI PostCurve : public DataProperty::DataBase
	{
	public:
		PostCurve() = default;
		~PostCurve() = default;
		virtual void copy(DataBase *data) override;

		void setDescribe(QString d);
		QString getDescribe();
		void setXVariable(QString x);
		QString getXVariable();
		void setYVariable(QString y);
		QString getYVariable();
		void setFile(QString f);
		QString getFile();

	private:
		QString _describe{};
		QString _xVariable{};
		QString _yVariable{};
		QString _file{};
	};

}

#endif