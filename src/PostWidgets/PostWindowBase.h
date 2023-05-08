/**
 * @file PostWindowBase.h
 * @brief 绘图窗口基类（2D、3D）
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 16:47
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
#ifndef _POSTWINDOWBASE_H_
#define _POSTWINDOWBASE_H_

#include "PostWidgetsAPI.h"
#include "ModuleBase/graphWindowBase.h"
#include <QWidget>
#include <QList>

class QToolBar;
class SARibbonCategory;

namespace GUI
{
	class MainWindow;
}

namespace Post
{
	enum PostWindowType
	{
		UnDefined = 0,
		D2,
		D3,
		D2D3,
	};

	/**
	 * @brief 绘图窗口基类（2D、3D）
	 * @since 2.5.0
	 */
	class POSTAPI PostWindowBase : public ModuleBase::GraphWindowBase
	{
		Q_OBJECT
	public:
		PostWindowBase(GUI::MainWindow *mainwindow, int proID, ModuleBase::GraphWindowType gt, PostWindowType type);
		~PostWindowBase();
		//设置类型
		void setWindowType(PostWindowType type);
		//获取类型
		PostWindowType getPostWindowType();
		//添加绘图窗口
		void appendGraphWindow(ModuleBase::GraphWindowBase *g);
		//移除窗口
		void removeGraphWindow(ModuleBase::GraphWindowBase *g);
		//移除第index个绘图窗口
		void removeGraphWindow(int index);
		//清空全部绘图窗口
		void removeAllGraphWindow();
		//设置树形窗口
		void setTreeWidget(QWidget *w);
		//获取树形窗口
		QWidget *getTreeWidget();
		//设置属性窗口
		void setPropWidget(QWidget *w);
		//获取属性窗口
		QWidget *getPropWidget();
		//添加工具条
		void appendToolBar(QToolBar *toolbar);
		//移除工具条
		void removeToolBar(QToolBar *toolbar);
		//获取全部工具条
		QList<QToolBar *> getToolBarList();
		virtual void setView(QString view) override;
		virtual void setViewValue(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3) override;

	signals:
		//关闭窗口信号
		void closeWindowSignal(Post::PostWindowBase *w);

	protected:
		void closeEvent(QCloseEvent *e) override;

	protected:
		PostWindowType _windowType{UnDefined};
		QList<ModuleBase::GraphWindowBase *> _graphWidgetList{};

		QWidget *_treeWidget{};
		QWidget *_propWidget{};
		QList<QToolBar *> _toolBarList{};
		SARibbonCategory *_3dRender_page{};
	};
}

#endif
