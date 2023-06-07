#include "DebugLogger.h"

#include <cstdio>
#include <cstring>
#include <ctime>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define filename(x) strrchr(x, '\\') ? strrchr(x, '\\') + 1 : x
#else
#define filename(x) strrchr(x, '/') ? strrchr(x, '/') + 1 : x
#endif

namespace Common {
	void DebugLogger::info(const char* file, int line, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		output(file, line, format, 0, args);
		va_end(args);
	}

	void DebugLogger::warning(const char* file, int line, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		output(file, line, format, 1, args);
		va_end(args);
	}

	void DebugLogger::error(const char* file, int line, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		output(file, line, format, 2, args);
		va_end(args);
	}

	char* DebugLogger::currentTime()
	{
		time_t	   rawtime;
		struct tm* timeS;
		char*	   buffer = new char[80];

		time(&rawtime);

		timeS = localtime(&rawtime);
		sprintf(buffer, "%d-%s%d-%s%d %s%d:%s%d:%s%d", timeS->tm_year + 1900,
				timeS->tm_mon < 10 ? "0" : "", timeS->tm_mon, timeS->tm_mday < 10 ? "0" : "",
				timeS->tm_mday, timeS->tm_hour < 10 ? "0" : "", timeS->tm_hour,
				timeS->tm_min < 10 ? "0" : "", timeS->tm_min, timeS->tm_sec < 10 ? "0" : "",
				timeS->tm_sec);
		return buffer;
	}

	/**
	 * 控制台显示控制格式：ESC[{attr1};{attr2};…;{attrn}m
	 * 显示方式：
	 *		0（默认值）
	 *		1（高亮显示，顺便加粗？不确定）
	 *		2（暗淡）
	 *		22（非粗体，不确定）
	 *		4（下划线）
	 *		5（闪烁，但是我没看出有什么效果。。）
	 *		25（非闪烁）
	 *		7（反显，我也没看出效果）
	 *		27（非反显）
	 *		8（隐藏）
	 *
	 * 字体颜色：
	 *		30（黑色）
	 *		31（红色）
	 *		32（绿色）
	 *		33（黄色）
	 *		34（蓝色）
	 *		35（品红）
	 *		36（青色）
	 *		37（白色）
	 * 背景色：
	 *		40（黑色）
	 *		41（红色）
	 *		42（绿色）
	 *		43（黄色）
	 *		44（蓝色）
	 *		45（品红）
	 *		46（青色）
	 *		47（白色）
	 */
	void DebugLogger::output(const char* file, int line, const char* format, int level,
							 va_list args)
	{
		char type[15] = "";
		switch(level) {
			case 1:
				printf("\033[33m"); // 红色
				strcpy(type, "WARNING");
				break;
			case 2:
				printf("\033[31m"); // 黄色
				strcpy(type, "ERROR");
				break;
			default:
				strcpy(type, "INFO");
				break;
		}

		printf("[%s][%s:%d][%s]: ", currentTime(), filename(file), line, type);

		vprintf(format, args);
		printf("\033[0m");
	}
} // namespace Common
