#ifndef _BCTEMPERATURE_H_
#define _BCTEMPERATURE_H_

#include "BCScalarBase.h"

namespace BCBase
{
	/**
	 * @brief 温度边界条件
	 * @since 2.5.0
	 */
	class BCBASEAPI BCTemperature : public BCScalarBase
	{
	public:
		BCTemperature();
		~BCTemperature() = default;

	protected:
	private:
	};

}

#endif
