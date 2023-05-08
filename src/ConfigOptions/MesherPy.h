/**
 * @file MesherPy.h
 * @brief 网格剖分器python接口封装类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-06 10:46
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
#ifndef MESHERPY_H_
#define MESHERPY_H_
#include "ConfigOptionsAPI.h"

namespace ConfigOption
{
	/**
	 * @brief 网格剖分器python接口封装类
	 * @since 2.5.0
	 */
	class MesherPy
	{
	public:
		void static setValue(int index, char *name, char *stype, char *svalue);

	protected:
	private:
	};

}

extern "C"
{
	void CONFIGOPTIONSAPI setValue(int index, char *name, char *stype, char *svalue);
}

#endif