/**
 * @file DialogRemoveReport.h
 * @brief 报告移除确认对话框
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-07 10:20
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
#ifndef _REMOVEREPORTDIALOG_H_
#define _REMOVEREPORTDIALOG_H_

#include "SelfDefObject/QFDialog.h"

namespace GUI
{
	class MainWindow;
}
namespace Ui
{
	class RemoveReportDialog;
}

namespace ProjectTree
{
	class RemoveReportDialog : public QFDialog
	{
		Q_OBJECT
	public:
		RemoveReportDialog(GUI::MainWindow *m);
		~RemoveReportDialog();

		bool isRemoveCompletely();

	private:
		Ui::RemoveReportDialog *_ui{};
	};
}

#endif
