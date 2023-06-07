/**
 * @file main.cpp
 * @brief FastCAE程序入口文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 15:34
 * @copyright Copyright (c) Since 2020  青岛数智船海科技有限公司  All rights reserved.
 *
 * ============================================================================
 * Program:   FastCAE
 *
 * Copyright (c) 青岛数智船海科技有限公司 Since 2020 All rights reserved.
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
#include "CommandLine.h"
#include "FastCAEVersionMacros.h"
#include "MainWindow/MainWindow.h"
#include "XBeautyUI.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QOpenGLContext>
#include <QProcess>
// #include "ConfigOptions/ConfigDataReader.h"
// #include "ConfigOptions/ConfigOptions.h"
// #include "ConfigOptions/GlobalConfig.h"
#include "Common/DebugLogger.h"
#include "Settings/BusAPI.h"

#ifdef Q_OS_WIN
#include "License/confirmation.h"
#ifdef _DEBUG
#include <crtdbg.h>
#endif
#endif

#define CHECKINGMEMORY 0

bool testOpenGL()
{
	bool		   supportOpenGLCore	= false;
	QString		   currentOpenGLVersion = "";
	QOpenGLContext ctx;
	if(ctx.create()) {
		auto version = ctx.format();
		if(version.majorVersion() > 3
		   || (version.majorVersion() == 3 && version.minorVersion() >= 3)) {
			supportOpenGLCore = true;
		} else {
			currentOpenGLVersion =
				QString("%1.%2").arg(version.majorVersion()).arg(version.minorVersion());
		}
	}
	if(!supportOpenGLCore) {
		QMessageBox::critical(nullptr, "OpenGL Error",
							  "Startup failed: FastCAE requires OpenGL version greater than or "
							  "equal to 3.3, but the current version is "
								  + currentOpenGLVersion,
							  QMessageBox::Ok);
	}
	return supportOpenGLCore;
}
/**
 * @brief 程序的入口函数
 * @param argc 命令行参数的个数
 * @param argv 命令行参数数组
 * @return int 返回函数运行结果
 * @since 2.5.0
 */
int main(int argc, char* argv[])
{
	// 添加Qt的对高分屏的支持
#if(QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	CommandPara para(argc, argv);
	if(para.isHelp())
		return 1;

	QApplication app(argc, argv);
	if(!testOpenGL()) {
		return 1;
	}
	// 	QString path = qApp->applicationDirPath();
	// 	ConfigOption::ConfigDataReader reader(path + "/../ConfigFiles/",
	// ConfigOption::ConfigOption::getInstance()); 	reader.read(); 	QString qUseRibbon =
	// ConfigOption::ConfigOption::getInstance()->getGlobalConfig()->getUseRibbon(); 	bool
	// bUseRibbon = qUseRibbon == "yes" ? true : false;

	bool			isRibbon = Setting::BusAPI::instance()->isUseRibbon();

	GUI::MainWindow mainwindow(isRibbon);

	/******************************************************************************/
	XBeautyUI::instance()->setQssFilePath(":/Beauty/QUI/beauty/qianfan.qss");
	XBeautyUI::instance()->autoSetStyle();
	QString qssFileName = XBeautyUI::instance()->qssFilePath();

	//**************加载qss******************
	QFile	qssFile(qssFileName);
	if(qssFile.exists()) {
		qssFile.open(QIODevice::ReadOnly);
		QString style = qssFile.readAll();
		qApp->setStyleSheet(style);
		qssFile.close();
	}
	//*****************************************

	//***************正版验证******************
#ifdef Q_OS_WIN
	// 	Confirmation confirm;
	// 	confirm.setParent(&mainwindow);
	// 	if (!confirm.licenseCheck())
	// 	{
	// 		return 0;
	// 	}
#endif
	//*****************************************

	if(para.exec(&mainwindow))
		emit mainwindow.sendInfoToStatesBar(QString("Version: %1").arg(FASTCAE_VERSION));
	else
		return 1;

	int e = app.exec();

#ifdef Q_OS_WIN
#ifdef _DEBUG

	// 	if (CHECKINGMEMORY)
	// 	{
	// 		printf("check memory leak ...\n");
	// 		_CrtDumpMemoryLeaks();
	// 		printf("check over.\n");
	// 	}
	//
#endif
#endif

	if(e == -1000) {
		QProcess::startDetached(qApp->applicationFilePath(), QStringList());
		return 0;
	}

	return e;
}
