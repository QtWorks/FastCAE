#ifndef _BCPRESSURE_H_
#define _BCPRESSURE_H_

#include "BCVectorBase.h"

namespace BCBase
{
	/**
	 * @brief 压力边界条件
	 * @since 2.5.0
	 */
	class BCBASEAPI BCPressure : public BCVectorBase
	{
	public:
		BCPressure();
		~BCPressure() = default;

	protected:
	};

}

#endif