/**
 * @file BusAPI.h
 * @brief 设置信息管理单例类头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 16:40
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
#ifndef _SETTINGBUSAPI_H_
#define _SETTINGBUSAPI_H_

#include <QString>
#include <QStringList>
#include <QColor>
#include "SettingAPI.h"

namespace GUI
{
	class MainWindow;
}

/**
 * @brief 跟设置有关的命名空间
 * @since 2.5.0
 */
namespace Setting
{
	class MainSetting;
	// 	class SolverManager;
	// 	class SolveOption;
	class GraphOption;
	class MessageSetting;

	class SETTINGAPI BusAPI
	{
	public:
		/**
		 * @brief 获取设置信息管理类的实例对象
		 * @return BusAPI* 返回设置信息管理类的单例对象
		 * @since 2.5.0
		 */
		static BusAPI *instance();
		/**
		 * @brief 将设置信息写出ini配置文件
		 * @since 2.5.0
		 */
		void writeINI();
		/**
		 * @brief 设置工作空间
		 * @since 2.5.0
		 */
		void setWorkingDir();
		// 		void setDesignModel(bool m);
		// 		bool isDesignModel();
		/**
		 * @brief 获取工作空间
		 * @return QString 返回工作空间的路径
		 * @since 2.5.0
		 */
		QString getWorkingDir();
		//		void setSolver();
		/**
		 * @brief 设置本地化语言（“Chinese”或者“English”）
		 * @param lang 要设置的本地化语言
		 * @since 2.5.0
		 */
		void setLanguage(const QString lang);
		/**
		 * @brief 获取本地化语言
		 * @return QString 返回本地化语言的值（“Chinese”或者“English”）
		 * @since 2.5.0
		 */
		QString getLanguage();
		// 		SolverManager* getSolverManager();
		// 		void setSolverOptions();
		// 		SolveOption* getSolveOptions();
		/**
		 * @brief 打开绘图选项对话框
		 * @deprecated 该函数名语义不明确，请使用showGraphOptionsDialog()代替
		 * @since 2.5.0
		 */
		void setGraphOptions();
		/**
		 * @brief 打开绘图选项对话框
		 * @since 2.5.0
		 */
		void showGraphOptionsDialog();
		/**
		 * @brief 获取绘图选项设置对象
		 * @return GraphOption* 返回绘图选项设置对象
		 * @since 2.5.0
		 */
		GraphOption *getGraphOption();
		/**
		 * @brief 获取最近打开文件的列表
		 * @return QStringList 返回最近打开文件的列表
		 * @since 2.5.0
		 */
		QStringList getRencetFiles();
		/**
		 * @brief 添加文件到最近打开的文件列表
		 * @param f 要添加到最近打开文件列表的文件
		 * @since 2.5.0
		 */
		void appendRecentFile(QString f);
		/**
		 * @brief 设置已经加载的插件列表
		 * @param p 已经加载的插件列表
		 * @since 2.5.0
		 */
		void setPlugins(QStringList p);
		/**
		 * @brief 获取已经加载的插件列表
		 * @return QStringList 返回已经加载的插件列表
		 * @since 2.5.0
		 */
		QStringList getPlugins();
		/**
		 * @brief 设置是否显示用户引导页面
		 * @param s 是否显示用户引导页面的布尔值
		 * @since 2.5.0
		 */
		void isEnableUserGuidence(bool s);
		/**
		 * @brief 获取是否显示用户引导页面
		 * @return bool 返回是否显示用户引导页面的布尔值
		 * @since 2.5.0
		 */
		bool isEnableUserGuidence();
		/**
		 * @brief 设置是否使用Ribbon风格
		 * @param on 是否使用Ribbon风格的布尔值
		 * @since 2.5.0
		 */
		void isUseRibbon(bool on);
		/**
		 * @brief 获取是否使用Ribbon风格
		 * @return bool 返回是否使用Ribbon风格的布尔值
		 * @since 2.5.0
		 */
		bool isUseRibbon();
		/**
		 * @brief 获取License文件的路径
		 * @return QString 返回License文件的路径
		 * @since 2.5.0
		 */
		QString getLicensePath() const;
		/**
		 * @brief 设置License文件
		 * @param licensePath License文件的路径
		 * @since 2.5.0
		 */
		void setLicensePath(const QString &licensePath);
		/**
		 * @brief 获取主窗口对象
		 * @return GUI::MainWindow* 返回主窗口对象
		 * @since 2.5.0
		 */
		GUI::MainWindow *getMainWindow();
		/**
		 * @brief 设置主窗口对象
		 * @param mw 主窗口对象
		 * @since 2.5.0
		 */
		void setMainWindow(GUI::MainWindow *mw);

		int getMessageShowMode() const;

		void setMessageShowMode(int showMode);

		bool getMessageShowType() const;

		void setMessageShowType(bool showType);

		bool getMessageShowTime() const;

		void setMessageShowTime(bool showTime);

		int getMessageFontPts() const;

		void setMessageFontPts(int fontPts);

		QColor getMessageBkColor() const;

		void setMessageBkColor(const QColor &bkColor);

	private:
		/**
		 * @brief 构造函数
		 * @since 2.5.0
		 */
		BusAPI();
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~BusAPI();
		/**
		 * @brief 从ini文件读取配置信息
		 * @since 2.5.0
		 */
		void readINI();

	private:
		/**
		 * @brief 配置信息管理类的单例对象
		 * @since 2.5.0
		 */
		static BusAPI *_ins;
		/**
		 * @brief 主窗口配置信息类对象
		 * @since 2.5.0
		 */
		MainSetting *_mainSetting{};
		// 		SolverManager* _solvers{};
		// 		SolveOption* _solveOption{};
		/**
		 * @brief 绘图选项配置信息类对象
		 * @since 2.5.0
		 */
		GraphOption *_graphOption{};
		/**
		 * @brief 输出消息配置信息类对象
		 * @since 2.5.0
		 */
		MessageSetting *_messageSetting{};
		/**
		 * @brief 主窗口对象
		 * @since 2.5.0
		 */
		GUI::MainWindow *_mainWindow{};
		//		bool _isDesignModel{ false };
	};
}

#endif