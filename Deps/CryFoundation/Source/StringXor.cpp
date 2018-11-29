#include <StringXor.h>
namespace Cry
{
	namespace Text
	{
		std::string Xor::Operate(std::string lpszSource) noexcept
		{
			for (uint32_t i = 0; i < lpszSource.size(); ++i)
			{
				if (i % 2)
				{
					lpszSource[i] = lpszSource[i] ^ DynamicSource[(i % (sizeof(DynamicSource) / sizeof(int8_t)) >> 8)];
				}
				else
				{
					lpszSource[i] = lpszSource[i] ^ StaticSource[(i % (sizeof(StaticSource) / sizeof(int8_t)) >> 8)];
				}
			}
			return lpszSource;
		}
	}
}