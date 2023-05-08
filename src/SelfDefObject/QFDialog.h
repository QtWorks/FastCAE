/**
 * @file QFDialog.h
 * @brief 对话框基类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 18:19
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
#ifndef _QFDIALOG_H_
#define _QFDIALOG_H_

#include <QDialog>
#include "SelfDefObjectAPI.h"

namespace GUI
{
	class MainWindow;
}

/**
 * @brief 对话框基类
 * @since 2.5.0
 */
class SELFDEFINEOBJAPI QFDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * @brief 构造函数
	 * @param m 主窗口对象
	 * @param key
	 * @since 2.5.0
	 */
	QFDialog(GUI::MainWindow *m, bool key = true);
	/**
	 * @brief 析构函数
	 * @since 2.5.0
	 */
	~QFDialog();
	/**
	 * @brief 将对话框显示为模态对话框，在用户关闭它之前一直处于阻塞状态
	 * @return int 返回一个DialogCode结果
	 * @retval QDialog::Accepted 用户点击了确认键
	 * @retval QDialog::Rejected 用户点击了取消键
	 * @since 2.5.0
	 */
	virtual int exec() override;

signals:
	void endaleGraphWinKey(bool on);

protected:
	/**
	 * @brief 主窗口对象
	 * @since 2.5.0
	 */
	GUI::MainWindow *_mainWindow{};
	/**
	 * @brief 设置键盘事件
	 * @since 2.5.0
	 */
	bool _keySig{true};
};

#endif