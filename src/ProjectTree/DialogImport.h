/**
 * @file DialogImport.h
 * @brief 导入组件对话框
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-07 10:14
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
#ifndef _DIALOGIMPORTMESHSET_
#define _DIALOGIMPORTMESHSET_

#include "ModuleBase/componentDialogBase.h"

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
	enum ImportType
	{
		None,
		Geometry,
		MeshSet
	};
	/**
	 * @brief 导入组件对话框类
	 * @since 2.5.0
	 */
	class ImportDialog : public ModuleBase::ComponentSelectDialogBase
	{
		Q_OBJECT
	public:
		ImportDialog(GUI::MainWindow *mainwindow, ModelData::ModelDataBaseExtend *data, ImportType t);
		~ImportDialog() = default;

	protected:
		void init() override;
		void accept() override;

	private:
		void initGeo();
		void initMeshSet();
		void initGeoComponent();

		void acceptGeo();
		//		void acceptComponents();

	private:
		ImportType _type{None};
		ModelData::ModelDataBaseExtend *_data{};
	};

}

#endif
