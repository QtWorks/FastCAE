/**
 * @file Post3DInterface.h
 * @brief 三维曲线绘图接口
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 16:40
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
#ifndef _POST3DWINDOWINTERFACE_H_
#define _POST3DWINDOWINTERFACE_H_

#include "PostWindowBase.h"

namespace GUI
{
	class MainWindow;
}

namespace Ui
{
	class Post3DInterface;
}

namespace Post
{
	class Post3DWindow;
	/**
	 * @brief 三维曲线绘图接口类
	 * @since 2.5.0
	 */
	class POSTAPI Post3DWindowInterface : public PostWindowBase
	{
	public:
		Post3DWindowInterface(GUI::MainWindow *m, int proid);
		~Post3DWindowInterface();
		//获取三维绘图窗口
		Post3DWindow *getWindow();
		virtual void reTranslate() override;
		void saveImage(QString fileName, int width, int heigh, bool showDlg) override;

	private:
		void init();

	private:
		Ui::Post3DInterface *_ui{};
		Post3DWindow *_post3DWindow{};
	};
}

#endif
