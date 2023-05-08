/**
 * @file PlotWidget.h
 * @brief 二维曲线绘制类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 14:16
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
#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include "PostPlotWidgetAPI.h"
#include <qwt_plot.h>
#include <QList>
#include <QMenu>
#include <QAction>

class QwtPlotGrid;

namespace PostPlot
{

	/**
	 * @brief 二维曲线绘制类
	 * @since 2.5.0
	 */
	class POSTPLOTWIDGETAPI PlotWidget : public QwtPlot
	{
		Q_OBJECT
	public:
		PlotWidget(QWidget *parent = nullptr);

		~PlotWidget();

	public:
		//坐标轴重置
		// void replot();
		//添加测试曲线
		// void plot_addCurve();
		/**
		 * @brief 添加曲线
		 * @param name 曲线名称
		 * @param xData x轴数据
		 * @param yData y轴数据
		 * @since 2.5.0
		 */
		void plot_addCurve(QString name, QVector<double> &xData, QVector<double> &yData);
		/**
		 * @brief 删除曲线
		 * @param index 曲线索引
		 * @since 2.5.0
		 */
		void plot_removeCurve(int index);
		/**
		 * @brief 删除曲线
		 * @param curvename 曲线名称
		 * @since 2.5.0
		 */
		void plot_removeCurve(QString curvename);
		/**
		 * @brief 删除所有曲线
		 * @since 2.5.0
		 */
		void plot_removeAllCurves();
		/**
		 * @brief 更新曲线数据
		 * @param index 曲线索引
		 * @param xData x轴数据
		 * @param yData y轴数据
		 * @since 2.5.0
		 */
		void plot_updateCurve(int index, QVector<double> &xData, QVector<double> &yData);
		/**
		 * @brief 设置曲线标题
		 * @param title 标题
		 * @since 2.5.0
		 */
		void plot_setTitleName(QString title);
		/**
		 * @brief 设置曲线标题字体
		 * @param font 字体
		 * @since 2.5.0
		 */
		void plot_setTitleFont(QFont font);
		//设置标题字体大小
		void plot_setTitleFontSize(int size);
		//设置标题字体颜色
		void plot_setTitleFontColor(QColor color);
		//设置绘图区的背景颜色
		void plot_setBackGround(QColor color);
		//设置绘图区域网格化
		void plot_setPlotGrid(bool isgrid);
		//设置Legend位置 0-none 1-上 2-下 3-左 4-右
		void plot_setLegendPosition(int position);
		//设置legend是否可见
		void plot_setLegendVisible(int legned, bool flag);
		//设置坐标轴个数
		//（未实现）
		// void plot_setAxisNum(int num);
		//设置坐标轴名称
		void plot_setAxisName(int axis, QString name);
		//设置坐标轴字体颜色
		void plot_setAxisFontColor(int axis, QColor color);
		//设置坐标轴字体大小
		void plot_setAxisFontSize(int axis, int size);
		//设置坐标轴字体 0-宋体 1-黑体 2-Arial
		void plot_setAxisFont(int axis, QFont font);
		//设置坐标轴范围  axis-xBottom yLeft yRight xTop  reange[0]-min range[1]-max
		// void plot_setAxisRange(int axis, double min, double max);
		//设置坐标轴范围和跨步大小
		void plot_setAxisRangeSetp(int axis, double min, double max, double step);
		//设置坐标轴自动延伸
		void plot_setAxisScaleAuto(int axis, bool flas);
		//设置坐标轴标题是否显示
		void plot_setAxisVisible(int axis, bool flag);
		//设置曲线颜色
		void plot_setCurveColor(int colIndex, QColor color);
		//设置线型
		void plot_setCurveStyle(int colIndex, Qt::PenStyle style);
		//设置线宽
		void plot_setCurveWidth(int colindex, int width);
		//设置曲线名称
		void plot_setCurveName(int colindex, QString name);
		//是否显示数据点
		//(未实现)
		// void plot_setCurveShowPoint(QString fileName, int colindex, bool show);
		//设置曲线坐标轴索引
		//（未实现）
		// void plot_setCurveAxisIndex(QString fileName, int colindex, int axisIndex);

	private:
		/**
		 * @brief 初始化画布
		 */
		void initPlot();

	private:
		//画布辅助网格线
		QwtPlotGrid *_grid{nullptr};
		//曲线数量
		int _curveNum{0};
		// plot主标题字体样式
		QFont _titlefont{};
		//坐标轴字体样式
		QFont _xBottomfont{};
		QFont _yLeftfont{};
		QFont _yRightfont{};
		QFont _xTopfont{};
		// plot主标题
		QwtText _title{};
		//坐标轴标题
		QwtText _xBottomtitle{};
		QwtText _yLefttitle{};
		QwtText _yRighttitle{};
		QwtText _xToptitle{};

		//曲线颜色
		QList<QColor> colorList = {QColor(0, 0, 0), QColor(255, 0, 0), QColor(0, 255, 0), QColor(0, 0, 255), QColor(0, 255, 255),
								   QColor(127, 0, 255), QColor(255, 255, 0), QColor(255, 0, 255), QColor(255, 127, 0), QColor(0, 127, 127)};
	};
}

#endif // PLOTWIDGET_H
