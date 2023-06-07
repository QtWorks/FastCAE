/**
 * @file DebugLogger.h
 * @brief 用于输出调试信息的类
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2023-05-11 16:12
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
#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H

#include "CommonAPI.h"

#include <cstdarg>

namespace Common {
	class COMMONAPI DebugLogger {
	public:
		DebugLogger()  = delete;
		~DebugLogger() = delete;

	public:
		static void info(const char* file, int line, const char* format, ...);
		static void warning(const char* file, int line, const char* format, ...);
		static void error(const char* file, int line, const char* format, ...);

	protected:
		static char* currentTime();
		static void output(const char* file, int line, const char* format, int level, va_list args);
	};
} // namespace Common

// 用宏OUTPUT_DEBUG_INFO控制调试信息是否输出的开关
#ifdef OUTPUT_DEBUG_INFO
#define DebugInfo(FORMAT, ...) Common::DebugLogger::info(__FILE__, __LINE__, FORMAT, __VA_ARGS__)
#define DebugWarn(FORMAT, ...) Common::DebugLogger::warning(__FILE__, __LINE__, FORMAT, __VA_ARGS__)
#define DebugError(FORMAT, ...) Common::DebugLogger::error(__FILE__, __LINE__, FORMAT, __VA_ARGS__)
#else
#define DebugInfo(FORMAT, ...)
#define DebugWarn(FORMAT, ...)
#define DebugError(FORMAT, ...)
#endif // OUTPUT_DEBUG_INFO

#endif