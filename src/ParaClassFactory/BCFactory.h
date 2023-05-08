/**
 * @file BCFactory.h
 * @brief 边界条件工厂类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 14:27
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
#ifndef _BCFACTORY_H_
#define _BCFACTORY_H_

#include "ParaClassFactoryAPI.h"
#include "BCBase/BCType.h"
#include "DataProperty/modelTreeItemType.h"

namespace BCBase
{
	class BCBase;
}

namespace ParaClassFactory
{
	/**
	 * @brief 边界条件工厂类
	 * @since 2.5.0
	 */
	class PARACLASSFACTORYAPI BCFactory
	{
	public:
		BCFactory() = default;
		~BCFactory() = default;

		static BCBase::BCBase *createBCByText(QString text);
		static BCBase::BCBase *createBCByType(BCBase::BCType type, QString name, ProjectTreeType t);
	};

}

#endif