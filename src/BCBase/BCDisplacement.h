#ifndef _BCDISPLACEMENT_H_
#define _BCDISPLACEMENT_H_

#include "BCVectorBase.h"

namespace BCBase
{
	/**
	 * @brief 位移边界条件
	 * @since 2.5.0
	 */
	class BCBASEAPI BCDisplacement : public BCVectorBase
	{
	public:
		BCDisplacement();
		~BCDisplacement() = default;

	protected:
		};

}

#endif