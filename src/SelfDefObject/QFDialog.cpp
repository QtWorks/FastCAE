/**
 * @file QFDialog.cpp
 * @brief 对话框基类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 18:20
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
#include "QFDialog.h"
#include "MainWindow/MainWindow.h"

QFDialog::QFDialog(GUI::MainWindow *m, bool k) : _mainWindow(m), _keySig(k), QDialog(m)
{
	this->setAttribute(Qt::WA_DeleteOnClose, true);
	if (_keySig)
		connect(this, SIGNAL(endaleGraphWinKey(bool)), _mainWindow, SIGNAL(enableGraphWindowKeyBoard(bool)));

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
	if (_keySig)
		emit endaleGraphWinKey(false);
}
QFDialog::~QFDialog()
{
	if (_keySig)
		emit endaleGraphWinKey(true);
}

int QFDialog::exec()
{
	this->setAttribute(Qt::WA_DeleteOnClose, false);
	if (_keySig)
		emit endaleGraphWinKey(false);
	return QDialog::exec();
}
