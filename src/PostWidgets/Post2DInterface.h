/**
 * @file Post2DInterface.h
 * @brief 二维曲线绘图接口
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 16:38
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
#ifndef _POST2DINTERFACE_H_
#define _POST2DINTERFACE_H_

#include "PostWindowBase.h"
#include <QHash>
#include <QVector>

class QTextStream;

namespace Ui
{
	class Post2DInterface;
}
namespace GUI
{
	class MainWindow;
}

namespace Post
{
	class Post2DWindow;
	/**
	 * @brief 二维曲线绘图接口类
	 * @since 2.5.0
	 */
	class POSTAPI Post2DWindowInterface : public PostWindowBase
	{
	public:
		Post2DWindowInterface(GUI::MainWindow *m, int proid);
		~Post2DWindowInterface();
		void reTranslate() override;
		/**
		 * @brief 获取二维绘图窗口
		 * @return Post2DWindow* 二维绘图窗口对象
		 * @since 2.5.0
		 */
		Post2DWindow *getWindow();
		/**
		 * @brief 打开数据文件，读取数据到_values
		 * @param fileName 文件名称
		 * @since 2.5.0
		 */
		void openfile(QString fileName);
		/**
		 * @brief 添加曲线
		 * @param name 曲线名称
		 * @param f 数据文件
		 * @param x 作为x轴的列名
		 * @param y 作为y轴的列名
		 * @since 2.5.0
		 */
		void addCurve(QString name, QString f, QString x, QString y);
		/**
		 * @brief 移除曲线
		 * @param name 曲线名称
		 * @since 2.5.0
		 */
		void removeCurve(QString name);
		/**
		 * @brief 生成图片
		 * @param fileName 图片路径
		 * @param width 图片宽度
		 * @param heigh 图片高度
		 * @param showDlg 是否显示对话框
		 * @since 2.5.0
		 */
		void saveImage(QString fileName, int width, int heigh, bool showDlg) override;

	private:
		QString readLine();
		/**
		 * @brief 从_values获取数据
		 * @param f 文件名
		 * @param va 列名
		 * @return QVector<double> 返回的数据数组
		 * @since 2.5.0
		 */
		QVector<double> getData(QString f, QString va);

	private:
		Ui::Post2DInterface *_ui{};
		/**
		 * @brief 二维绘图窗口
		 * @since 2.5.0
		 */
		Post2DWindow *_post2DWindow{};

		QTextStream *_stream{};
		/**
		 * @brief 绘图数据(QHash<文件路径，QHash<列名，QVector<列数据>>>)
		 * @since 2.5.0
		 */
		QHash<QString, QHash<QString, QVector<double>>> _values{};
	};
}

#endif
