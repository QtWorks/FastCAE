/**
 * @file DialogWorkingDir.h
 * @brief 工作目录设置对话框类头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 17:37
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
#ifndef _GIALOGWORKINGDIR_H_
#define _GIALOGWORKINGDIR_H_

//#include "SelfDefObject/QFDialog.h"
#include <QDialog>

namespace Ui
{
	class DialogWorkingDir;
}
namespace GUI
{
	class MainWindow;
}

namespace Setting
{
	class MainSetting;

	/**
	 * @brief 工作目录设置对话框类
	 * @since 2.5.0
	 */
	class WorkingDirDialog : public QDialog
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param mw 主窗口对象
		 * @param setting 主窗口配置信息对象
		 * @since 2.5.0
		 */
		WorkingDirDialog(GUI::MainWindow *mw, MainSetting *setting);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~WorkingDirDialog();

	private:
		/**
		 * @brief 用_setting初始化工作目录设置对话框
		 * @since 2.5.0
		 */
		void init();
		/**
		 * @brief 确认按钮的响应函数
		 * @since 2.5.0
		 */
		void accept() override;
		/**
		 * @brief 取消按钮的响应函数
		 * @since 2.5.0
		 */
		void reject() override;
		/**
		 * @brief 重写Dialog的closeEvent事件
		 * @param e QCloseEvent
		 * @since 2.5.0
		 */
		void closeEvent(QCloseEvent *e);

	private slots:
		/**
		* @brief 选择工作目录按钮点击的处理函数
		* @since 2.5.0
		*/
		void on_pushButton_clicked();

	private:
		/**
		 * @brief 主窗口配置信息管理类对象
		 * @since 2.5.0
		 */
		MainSetting *_setting{};
		/**
		 * @brief 工作目录设置对话框的ui对象
		 * @since 2.5.0
		 */
		Ui::DialogWorkingDir *_ui{};
	};

}

#endif
