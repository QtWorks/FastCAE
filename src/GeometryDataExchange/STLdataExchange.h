/**
* @file STLdataExchange.h
* @brief stl文件操作类头文件
* @author FastCAE研发小组(fastcae@diso.cn)
* @version 2.5.0
* @date 2022-03-24 10:20
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

#ifndef _STLDATAEXCHANGE_H__
#define _STLDATAEXCHANGE_H__

#include "GeometryThreadBase.h"

namespace GUI
{
	class MainWindow;
}

namespace Geometry
{
	class GeometrySet;

	class GEOMETRYDATAEXCHANGEAPI STLdataExchange : public GeometryThreadBase
	{
	public:
		STLdataExchange(const QString& fileName, GeometryOperation operation, GUI::MainWindow *mw,
			            QList<GeometrySet*>& res, int KernalId = -1);

		~STLdataExchange();

		void run() override;

	private:
		bool readSTL();
		
		void deriveGeometryTaskFinished();

	private:
		/**
		 * @brief 要操作的文件
		 * @since 2.5.0
		 */
		const QString _fileName;
		/**
		 * @brief 要执行的操作
		 * @since 2.5.0
		 */
		GeometryOperation _operation;
		/**
		 * @brief 是否为读操作
		 * @since 2.5.0
		 */
		bool _isRead{ false };
		/**
		 * @brief 是否为写操作
		 * @since 2.5.0
		 */
		bool _isWrite{ false };


	};

 
}

#endif // !_STLDATAEXCHANGE_H__

