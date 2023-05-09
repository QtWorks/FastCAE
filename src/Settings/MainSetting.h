/**
 * @file MainSetting.h
 * @brief 主窗口配置信息管理类头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 17:33
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
#ifndef _MainSetting_H_
#define _MainSetting_H_

#include <QString>
#include <QStringList>
#include <QVector>
#include <QIcon>
#include <QMap>

class QSettings;

namespace Setting
{
	class MainSetting
	{

	public:
		MainSetting() = default;
		~MainSetting() = default;

		void writeINI(QSettings *seeting);
		void readINI(QSettings *seeting);

		void setWorkingDir(const QString &dir);
		QString getWorkingDir() const;
		void setLanguage(const QString &lang);
		QString getLanguage();
		//添加最新打开文件
		void appendRecentFile(QString f);
		QStringList getRencentFile();
		//插件
		void setPlugins(QStringList ps);
		QStringList getPlugins();

		void isShowUserGuidance(bool s);
		bool isShowUserGuidance();

		void isUseRibbon(bool on);
		bool isUseRibbon();

		void setLicensePath(const QString &path);
		QString getLicensePath() const;

	private:
		QString _workingDir;
		QString _language{"English"};
		QStringList _recentFiles{};
		QString _licensePath;
		QStringList _plugins{};
		bool _showUserGuidance{true};
		bool _useRibbon{true};
	};

}

#endif
