/**
 * @file DialogAddBC.h
 * @brief 设置边界条件对话框
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-07 10:03
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
#ifndef _DIALOGADDBC_H_
#define _DIALOGADDBC_H_

#include "SelfDefObject/QFDialog.h"

namespace Ui
{
	class AddBCDialog;
}
namespace GUI
{
	class MainWindow;
}
namespace ModelData
{
	class ModelDataBaseExtend;
}

namespace ProjectTree
{
	/**
	 * @brief 设置边界条件对话框类
	 * @since 2.5.0
	 */
	class AddBCDialog : public QFDialog
	{
		Q_OBJECT
	public:
		AddBCDialog(GUI::MainWindow *m, ModelData::ModelDataBaseExtend *data);
		~AddBCDialog();

	private:
		/**
		 * @brief 初始化对话框数据
		 * @since 2.5.0
		 */
		void init();
		/**
		 * @brief 初始化边界条件列表
		 * @since 2.5.0
		 */
		virtual void initBCType();
		/**
		 * @brief 初始化组件列表
		 * @since 2.5.0
		 */
		virtual void initComponents();
		virtual void accept() override;

	private:
		Ui::AddBCDialog *_ui{};
		ModelData::ModelDataBaseExtend *_data{};
	};

}

#endif