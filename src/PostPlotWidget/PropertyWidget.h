/**
 * @file PropertyWidget.h
 * @brief 二维绘图plot属性设置窗口（右键菜单）
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 14:07
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
#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>
#include "PostPlotWidgetAPI.h"
#include <qwt_plot_dict.h>
#include "PlotWidget.h"
#include "PostCurveDataManager/PostData.h"
#include "PostCurveDataManager/PostCurveData.h"
#include "PostCurveDataManager/CurveDataReader.h"

namespace Ui
{
	class PropertyWidget;
}

namespace PostPlot
{
	/**
	 * @brief 二维绘图plot属性设置窗口
	 * @since 2.5.0
	 */
	class POSTPLOTWIDGETAPI PropertyWidget : public QWidget
	{
		Q_OBJECT

	public:
		PropertyWidget(PlotWidget *plotwidget, QWidget *parent = nullptr);
		~PropertyWidget();
		/**
		 * @brief 设置要显示的标签页
		 * @param index 标签页索引
		 * @since 2.5.0
		 */
		void showSetting(int index);
		/**
		 * @brief 读取曲线数据文件
		 * @param fileName 数据文件
		 * @since 2.5.0
		 */
		void read(QString fileName);
		/**
		 * @brief 数据源初始化（设置数据源下拉框）
		 * @since 2.5.0
		 */
		void datainit();
		/**
		 * @brief xy轴数据初始化（设置xy轴的数据项）
		 * @since 2.5.0
		 */
		void xyinit();

		/**
		 * @brief 添加算例曲线接口
		 * @param curvename 曲线名称
		 * @since 2.5.0
		 */
		void addCaseCurve(QString curvename);
		/**
		 * @brief 删除曲线
		 * @param curvename 曲线名称
		 * @since 2.5.0
		 */
		void delCaseCurve(QString curvename);

	private slots:

		//标题设置修改
		void modifyTitle();
		//标题调色板
		void titleColorButton();

		//坐标轴设置初始化
		void Axisinit(int index);
		//坐标轴调色板
		void AxisColor();
		//坐标轴设置修改
		void modifyAxis();

		//背景图例设置修改
		void modifyBackground();
		//背景调色板
		void BackColor();

		//读取文件中的变量
		void readFileData(int index);
		//根据XY添加曲线
		void addCurveOK();

		//获取曲线属性
		void SelectCurve(int index);
		//曲线属性修改
		void modifyCurve();
		//曲线调色板
		void CurveColor();
		//删除曲线
		void deleteCurve();

	private:
		//初始化
		void initPlotProperty();
		//信号连接
		void signalConnect();

	private:
		Ui::PropertyWidget *_ui{};
		PlotWidget *_plotwidget{nullptr};
		PostData::PostCurveData *_postcurvedata{nullptr};
		QList<PostData::PostDataPart *> _datapartlist{nullptr};
		PostData::CurveDataReader *_curvereader{nullptr};
	};

}
#endif // PROPERTYWIDGET_H
