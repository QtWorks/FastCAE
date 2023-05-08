/**
 * @file GlobalConfig.h
 * @brief 软件信息全局配置类
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
#ifndef _GOLBALCONFIG_H_
#define _GOLBALCONFIG_H_

#include "ConfigOptionsAPI.h"
#include <QString>

namespace ConfigOption
{
	/**
	 * @brief 软件信息全局配置类
	 * @since 2.5.0
	 */
	class CONFIGOPTIONSAPI GlobalConfig
	{
	public:
		GlobalConfig() = default;
		~GlobalConfig() = default;
		GlobalConfig(GlobalConfig *old);

		void setSoftName(QString name);
		QString getSoftName();
		void setChineseName(QString name);
		QString getChineseName();
		void setCorporation(QString c);
		QString getCorporation();
		void setWebsite(QString w);
		QString getWebsite();
		void setLogo(QString logo);
		QString getLogo();
		void setWelcome(QString w);
		QString getWelcome();
		void enableMaterial(bool m);
		void setVersion(QString v);
		QString getVersion();
		void setEMail(QString m);
		QString getEMail();
		bool isMaterialEnabled();
		void clearData();

		QString GetUserManual();				// Added xvdongming 2019-11-22
		void SetUserManual(QString userManual); // Added xvdongming 2019-11-22

		//		void setUseRibbon(const QString& str);
		//		const QString getUseRibbon() const;

	private:
		QString _softName{};
		QString _chineseName{};
		QString _corporation{};
		QString _website{};
		QString _logo{};
		QString _welcome{};
		QString _version{};
		QString _email{};
		QString _userManual{}; // Added xvdongming 2019-11-22
		bool _material{false};

		//		QString _useRibbon{};
	};

}

#endif
