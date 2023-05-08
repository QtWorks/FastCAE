/**
 * @file processBar.h
 * @brief 进度条类的头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-18 10:20
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
#ifndef _PROCESSBAR_H_
#define _PROCESSBAR_H_

#include "moduleBaseAPI.h"
#include <QWidget>

namespace Ui
{
	class ProcessBar;
}
namespace GUI
{
	class MainWindow;
}

namespace ModuleBase
{
	class ThreadTask;
	/**
	 * @brief 进度条类
	 * @since 2.5.0
	 */
	class MODULEBASEAPI ProcessBar : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口对象
		 * @param task 线程任务对象
		 * @param autoclose 任务结束，是否自动关闭进度条
		 * @since 2.5.0
		 */
		ProcessBar(GUI::MainWindow* mainWindow, ThreadTask* task, bool autoclose = true);
		/**
		 * @brief 构造函数
		 * @param mw 主窗口对象
		 * @param name 
		 * @param autoclose 任务结束，是否自动关闭进度条
		 * @since 2.5.0
		 */
		ProcessBar(GUI::MainWindow* mw, QString name, bool autoclose = true);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~ProcessBar();
		/**
		 * @brief 设置当前进度值
		 * @param d 要设置的进度值（0-100）
		 * @since 2.5.0
		 */
		void setProcess(int d);
		/**
		 * @brief 设置进度条是否在满进度（值为100）时自动关闭
		 * @param autoclose 是否自动关闭的布尔值
		 * @since 2.5.0
		 */
		void setAutoClose(bool autoclose);
		/**
		 * @brief 获取进度条是否自动关闭
		 * @return bool 返回是否自动关闭的布尔值
		 * @since 2.5.0
		 */
		bool isAutoClose();
		/**
		 * @brief 界面国际化翻译
		 * @since 2.5.0
		 */
		void reTranslate();
		/**
		 * @brief 设置进度值的最大、最小值
		 * @param min 最小值
		 * @param max 最大值
		 * @since 2.5.0
		 */
		void setProcessRange(int min, int max);
		/**
		 * @brief 设置进度条的为忙碌状态
		 * @since 2.5.0
		 */
		void setBusy();
		/**
		 * @brief 获取进度条的忙碌状态
		 * @return bool 返回的是否处于忙碌状态
		 * @since 2.5.0
		 */
		bool isBusy();
		/**
		 * @brief 设置进度条关闭按钮的显影状态
		 * @param on 是否显示关闭按钮
		 * @since 2.5.0
		 */
		void buttonVisible(bool on);
		/**
		 * @brief 设置进度条的标题信息
		 * @param s 标题信息
		 * @since 2.5.0
		 */
		void setInformation(QString s);



	signals:
		/**
		 * @brief 进度条关闭时触发该信号
		 * @since 2.5.0
		 */
		void closeProcess(QWidget*);
		void closeThread();

	private slots:
//		void peocessChanged(int p);
		/**
		 * @brief 进度条关闭按钮的单击事件响应槽函数
		 * @since 2.5.0
		 */
		void on_closeButton_clicked();
		/**
		 * @brief 界面是否自动关闭复选框的点击响应槽函数
		 * @since 2.5.0
		 */
		void onAutoCloseQCBClicked();

// 	protected:
// 		void closeEvent(QCloseEvent *);

	private:
		/**
		 * @brief 进度条的ui文件
		 * @since 2.5.0
		 */
		Ui::ProcessBar* _ui{};
		/**
		 * @brief 主窗口对象
		 * @since 2.5.0
		 */
		GUI::MainWindow* _mainWindow{};
		/**
		 * @brief 是否自动关闭
		 * @since 2.5.0
		 */
		bool _autoClose{ false };
		/**
		 * @brief 是否处于忙碌状态
		 * @since 2.5.0
		 */
		bool _isBusy{ false };

		/**
		 * @brief 与进度条关联的线程任务
		 * @since 2.5.0
		 */
		ThreadTask* _task{ nullptr };
	};
}

#endif
