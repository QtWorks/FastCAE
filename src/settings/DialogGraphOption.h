/**
 * @file DialogGraphOption.h
 * @brief 绘图选项设置对话框类头(.h)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 17:38
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
#ifndef DIALOGGRAPHOPTION_H_
#define DIALOGGRAPHOPTION_H_

//#include "SelfDefObject/QFDialog.h"
#include <QDialog>

namespace GUI
{
	class MainWindow;
}
namespace Ui
{
	class GraphOptionDialog;
}

namespace Setting
{
	class GraphOption;

	/**
	 * @brief 绘图选项设置对话框类
	 * @since 2.5.0
	 */
	class GraphOptionDialog : public QDialog
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainwindow 主窗口对象
		 * @param option 绘图信息配置类对象
		 * @since 2.5.0
		 */
		GraphOptionDialog(GUI::MainWindow *mainwindow, GraphOption *option);
		/**
		 * @brief 析构函数
		 * @since 2.5.0
		 */
		~GraphOptionDialog();

	signals:
		/**
		 * @brief 应用绘图选项对话框的配置信息时会触发此信号
		 * @since 2.5.0
		 */
		void updateGraph();

	private slots:
		/**
		 * @brief 点击绘图选项对话框的【确定】按钮会执行该槽函数
		 * @since 2.5.0
		 */
		void on_out_OkButton_clicked();
		/**
		 * @brief 点击绘图选项对话框的【应用】按钮会执行该槽函数
		 * @since 2.5.0
		 */
		void on_out_ApplyButton_clicked();
		/**
		 * @brief 点击绘图选项对话框的【取消】按钮会执行该槽函数
		 * @since 2.5.0
		 */
		void on_out_CancelButton_clicked();

	private:
		/**
		 * @brief 将绘图选项框的信息赋予_graphOption并触发updateGraph()信号
		 * @since 2.5.0
		 */
		void accept() override;
		/**
		 * @brief 用_graphOption对象初始化绘图选项对话框
		 * @since 2.5.0
		 */
		void init();

	private:
		/**
		 * @brief 绘图信息配置窗口的ui对象
		 * @since 2.5.0
		 */
		Ui::GraphOptionDialog *_ui{};
		/**
		 * @brief 主窗口对象
		 * @since 2.5.0
		 */
		GUI::MainWindow *_mainWindow{};
		/**
		 * @brief 绘图信息配置类对象
		 * @since 2.5.0
		 */
		GraphOption *_graphOption{};
	};

}

#endif
