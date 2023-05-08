/**
 * @file PostCustomPlot.h
 * @brief 该文件已经废弃
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 16:44
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
#ifndef _POSTCUSTOMPLOT_H_

#define _POSTCUSTOMPLOT_H_

#include <QWidget>
#include "PostWidgetsAPI.h"
//#include "CurveAnalyse/qcustomplot.h"

namespace Post
{
	/**
	 * @brief 该类已经废弃，后续版本会删除
	 * @since 2.5.0
	 */
	class POSTAPI PostCustomPlot /*: public QCustomPlot*/
	{
	public:
		PostCustomPlot(QWidget *w);
		~PostCustomPlot();

	protected:
	private:
	};

}

#endif