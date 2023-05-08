/**
 * @file ModuleBase.h
 * @brief 模板基类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 16:51
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
#ifndef _MODULEBASE_H_
#define _MODULEBASE_H_

#include "ModuleType.h"
#include "moduleBaseAPI.h"

class QTreeWidgetItem;

namespace GUI
{
	class MainWindow;
}

namespace ModuleBase
{
	/**
	 * @brief 模板基类
	 * @since 2.5.0
	 */
	class MODULEBASEAPI CModuleBase
	{
		//	Q_OBJECT
	public:
		CModuleBase(GUI::MainWindow *mainwindow, ModuleType type = Undefined);
		/*子类必须重写析构函数，防止内存泄漏 */
		virtual ~CModuleBase();
		const ModuleType getModuleType();
		virtual void reTranslate();

	protected:
		ModuleType _moduleType{Undefined};
		GUI::MainWindow *_mainWindow{};

	private:
	};

}

#endif