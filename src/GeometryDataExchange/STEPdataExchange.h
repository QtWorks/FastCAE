/**
 * @file STEPdataExchange.h
 * @brief step文件操作类头文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-18 15:42
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
#ifndef _STEPDATAEXCHANGE_H_
#define _STEPDATAEXCHANGE_H_

#include "GeometryThreadBase.h"

namespace Geometry
{
	/**
	 * @brief step格式几何文件操作（导入导出）类
	 * @since 2.5.0
	 */
	class GEOMETRYDATAEXCHANGEAPI STEPdataExchange : public GeometryThreadBase
	{
		public:
			/**
			 * @brief 构造函数
			 * @param _fileName 要操作的文件
			 * @param operation 要进行的操作
			 * @param mw 主窗口对象
			 * @param res 几何形状列表
			 * @param KernalId 
			 * @since 2.5.0
			 */
			STEPdataExchange(const QString& _fileName, GeometryOperation operation, GUI::MainWindow *mw, QList<GeometrySet*>& res, int KernalId = -1);
			/**
			 * @brief 析构函数
			 * @since 2.5.0
			 */
			~STEPdataExchange();
			void run() override;
		
		private:
			/**
			 * @brief 读取step文件
			 * @return bool 返回读取结果
			 * @since 2.5.0
			 */
			bool readStep();
			/**
			 * @brief 写入step文件
			 * @return bool 返回写入结果
			 * @since 2.5.0
			 */
			bool writeStep();
			void deriveGeometryTaskFinished();

		private:		
			/**
			 * @brief 要操作的文件名
			 * @since 2.5.0
			 */
			const QString _fileName;
			/**
			 * @brief 要执行的操作
			 * @since 2.5.0
			 */
			GeometryOperation _operation;
			/**
			 * @brief 是否为读取操作
			 * @since 2.5.0
			 */
			bool _isRead{ false };
			/**
			 * @brief 是否为写入操作
			 * @since 2.5.0
			 */
			bool _isWrite{ false };
	};
}
#endif