/**
 * @file CommandLine.cpp
 * @brief 命令行参数类源(.cpp)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 15:41
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
#include "CommandLine.h"
#include "MainWindow/MainWindow.h"
#include <iostream>
#include <QtCore>
#include <QtGui>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QFile>
#include "XBeautyUI.h"
#include "ConfigOptions/ConfigOptions.h"
#include "ConfigOptions/ConfigDataReader.h"
#include "ConfigOptions/GlobalConfig.h"
#include "PythonModule/PyAgent.h"
#include "MainWindow/MainWindowPy.h"
#include <QMessageBox>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#include <process.h>
#include <psapi.h>
#include <io.h>
#include <direct.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <sys/timeb.h>
#include <wchar.h>
#endif

#define WELCOMETIME 1500

CommandPara::CommandPara(int argc, char *argv[])
{

	for (int i = 1; i < argc; ++i)
	{
		QString arguement = QString(argv[i]).simplified().toLower();

		if (arguement == "-nogui")
		{
			_showGUI = false;
			Py::PythonAgent::getInstance()->setNoGUI(!_showGUI);
			continue;
		}

		else if (arguement == "-i")
		{
			char *c = argv[++i];
			_scriptFile = QString::fromLocal8Bit(c);
			continue;
		}
		else if (arguement.contains("-p"))
		{
			char *c = argv[++i];
			/*_projectFile = QString::fromLocal8Bit(c);*/
			_projectFile = QDir::fromNativeSeparators(QString::fromLocal8Bit(c));
			continue;
		}
		else if (arguement.contains("-help"))
		{
			_help = true;
			continue;
		}
	}

#ifdef Q_OS_WIN
	if (_help || (!_showGUI))
		connectToConsole();
#endif
}

bool CommandPara::isHelp()
{
	if (!_help)
		return false;
	std::cout << std::endl;
	std::cout << " -help    Show those help info" << std::endl;
	std::cout << " -i       Execute a script" << std::endl;
	std::cout << " -nogui   Run without GUI" << std::endl;
	std::cout << " -p       Open a project" << std::endl;
	return true;
}

bool CommandPara::exec(GUI::MainWindow *window)
{
	if (_showGUI)
	{
#ifndef _DEBUG
		//**************欢迎界面********************
		QString hello = ConfigOption::ConfigOption::getInstance()->getGlobalConfig()->getWelcome();
		QString helloPicName = qApp->applicationDirPath() + "/../ConfigFiles/Icon/" + hello;
		QSplashScreen *splash = new QSplashScreen;
		QFile helloPic(helloPicName);
		if (helloPic.exists())
		{
			splash->setPixmap(helloPicName);
			splash->setDisabled(true);
			splash->show();
			QElapsedTimer t;
			t.start();
			while (t.elapsed() < WELCOMETIME)
				QCoreApplication::processEvents();
			splash->finish(window);
			delete splash;
		}
		//*****************************************
#endif
		window->show();
		window->showMaximized();
	}

	if (!_projectFile.isEmpty())
	{
		QFile sf(_projectFile);
		if (!sf.exists())
			fileWarning(_projectFile, window);
		else
		{
			QString code = QString("MainWindow.openProjectFile(\"%1\")").arg(_projectFile);
			Py::PythonAgent::getInstance()->submit(code);
		}
	}
	bool runSc = false;
	if (!_scriptFile.isEmpty())
	{
		QFile sf(_scriptFile);
		if (!sf.exists())
			fileWarning(_scriptFile, window);
		else
		{
			Py::PythonAgent::getInstance()->execScript(_scriptFile);
			runSc = true;
		}
	}
	if (_showGUI)
		return true;
	else if (runSc)
		return true;
	return false;
}

void CommandPara::fileWarning(QString f, GUI::MainWindow *m)
{
	QString mess = QString(QObject::tr("\"%1\" is not exist!"));
	if (!_showGUI)
	{
		QByteArray array = mess.toLatin1();
		std::cout << mess.toLatin1().data() << std::endl;
	}
	else
		QMessageBox::warning(m, QString("Warning"), mess);
}

void CommandPara::connectToConsole()
{
#ifdef Q_OS_WIN
	if (!AttachConsole(ATTACH_PARENT_PROCESS))
		return;
	// redirect unbuffered stdout, stdin and stderr to the console
	{
		intptr_t lStdHandle = (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE);
		if (lStdHandle != (intptr_t)INVALID_HANDLE_VALUE)
		{
			int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
			if (hConHandle >= 0)
			{
				FILE *fp = _fdopen(hConHandle, "w");
				if (fp)
				{
					*stdout = *fp;
					setvbuf(stdout, NULL, _IONBF, 0);
				}
			}
		}
	}
	{
		intptr_t lStdHandle = (intptr_t)GetStdHandle(STD_INPUT_HANDLE);
		if (lStdHandle != (intptr_t)INVALID_HANDLE_VALUE)
		{
			int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
			if (hConHandle >= 0)
			{
				FILE *fp = _fdopen(hConHandle, "r");
				if (fp)
				{
					*stdin = *fp;
					setvbuf(stdin, NULL, _IONBF, 0);
				}
			}
		}
	}
	{
		intptr_t lStdHandle = (intptr_t)GetStdHandle(STD_ERROR_HANDLE);
		if (lStdHandle != (intptr_t)INVALID_HANDLE_VALUE)
		{
			int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
			if (hConHandle >= 0)
			{
				FILE *fp = _fdopen(hConHandle, "w");
				if (fp)
				{
					*stderr = *fp;
					setvbuf(stderr, NULL, _IONBF, 0);
				}
			}
		}
	}
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console
	// as well
	std::ios::sync_with_stdio();
#endif
}
