/**
 * @file FastCAEVersionMacros.h
 * @brief FastCAE版本号宏定义文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 15:37
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
#ifndef _FASTCAEVERSIONMACROS_H_
#define _FASTCAEVERSIONMACROS_H_

#define FASTCAE_MAJOR_VERSION 2
#define FASTCAE_MINOR_VERSION 5
#define FASTCAE_BUILD_VERSION 0

#define FASTCAE_VERSION "2.5.0"

/**************
0000 0000 0000
Maj  Min  Build
eg.
0002 0015 0035 -> V2.15.35
**************/
#define FASTCAE_VERSION_NUMBER (100000000ULL * FASTCAE_MAJOR_VERSION + 100000ULL * FASTCAE_MINOR_VERSION + FASTCAE_BUILD_VERSION)

#endif