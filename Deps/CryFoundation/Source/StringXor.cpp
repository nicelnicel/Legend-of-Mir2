#include <StringXor.h>
namespace Cry
{
	namespace Encrypt
	{
		std::string Xor::Operate(std::string lpszSource)
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
		uint32_t Xor::Operate(uint32_t uSource)
		{
			return (CrcTable[((sizeof(CrcTable) / sizeof(uint32_t)) & 0xFF) >> 8] ^ uSource) ^ 0xFFFFFFFF;
		}
	}
}