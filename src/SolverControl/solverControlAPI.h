/**
 * @file solverControlAPI.h
 * @brief 求解器控制类接口声明文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-12 15:35
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
#ifndef _SOLVERCONTROLAPI_H_
#define _SOLVERCONTROLAPI_H_

#include <QtCore/QtGlobal>


#if defined(SOLVERCONTROL_API)
#define SOLVERCONTROLAPI Q_DECL_EXPORT
#else
#define  SOLVERCONTROLAPI Q_DECL_IMPORT
#endif

#endif
