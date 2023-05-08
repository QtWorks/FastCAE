/**
 * @file DialogAssignMaterial.h
 * @brief 材料设置对话框
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-07 10:08
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
#ifndef _DIALOGASSIGNMATERIAL_H_
#define _DIALOGASSIGNMATERIAL_H_

#include "ModuleBase/componentDialogBase.h"

namespace GUI
{
	class MainWindow;
}
namespace ModelData
{
	class ModelDataBaseExtend;
}
class QHBoxLayout;
class QLabel;
class QComboBox;

namespace ProjectTree
{
	/**
	 * @brief 材料设置对话框类
	 * @since 2.5.0
	 */
	class AssignPropertyDialog : public ModuleBase::ComponentSelectDialogBase
	{
	public:
		AssignPropertyDialog(GUI::MainWindow *mainwindow, ModelData::ModelDataBaseExtend *data);
		~AssignPropertyDialog();

	private:
		void init() override;
		void accept() override;

	private:
		ModelData::ModelDataBaseExtend *_data{};
		QHBoxLayout *_layout{};
		QLabel *_label{};
		QComboBox *_combobox{};
	};

}

#endif