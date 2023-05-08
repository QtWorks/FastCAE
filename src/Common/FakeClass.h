#include "CommonAPI.h"

namespace Common
{
	class COMMONAPI FakeClass
	{
	public:
		FakeClass() = delete;
		~FakeClass() = default;
		int getNoUsedField();

	private:
		int m_NoUsedField = 0;
	};

} // namespace Common