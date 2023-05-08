#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include "CommonAPI.h"
namespace Common
{
	enum class Message : int
	{
		Unknown = 0,
		Normal,
		Warning,
		Error,
		Python
	};
}
#endif // !COMMONTYPES_H