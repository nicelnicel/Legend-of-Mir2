#pragma once
#include <cstdint>
#include <Helper>
#include <StringXor.h>
namespace Cry
{
	namespace Memory
	{
		class Masks
		{
		public:
			virtual ~Masks() = default;
		public:
			static uint32_t SearchMemory(const uint32_t uBeginAddress, const uint32_t uEndAddress, std::string lpszMasks, uint32_t uPos)
			{
				const char * pbSearchBuffer = lpszMasks.data();
				uint8_t * uResult = 0;
				uint32_t Pos = 0;
				try
				{
					for (uint8_t * pCur = reinterpret_cast<uint8_t*>(uBeginAddress); pCur < reinterpret_cast<uint8_t*>(uEndAddress); ++pCur)
					{
						if (*pCur != 0xCC && CryVirtualQueryMemory(uint8_t, pbSearchBuffer) == ((uint8_t)'\?') || *pCur == getByte(pbSearchBuffer))
						{
							if (!uResult)
							{
								uResult = pCur;
							}

							if (pbSearchBuffer += (CryVirtualQueryMemory(uint16_t, pbSearchBuffer) == ((uint16_t)'\?\?') || CryVirtualQueryMemory(uint8_t, pbSearchBuffer) != ((uint8_t)'\?')) ? 3 : 2; (!*pbSearchBuffer) || (!*(pbSearchBuffer - 1)) || (!*(pbSearchBuffer + 1)))
							{
								if (++Pos == uPos)
								{
									return reinterpret_cast<uint32_t>(uResult);
								}
								else
								{
									continue;
								}
							}
						}
						else if (uResult)
						{
							pCur = uResult;
							pbSearchBuffer = lpszMasks.data();
							uResult = 0;
						}
					}
				}
				catch (std::exception & e)
				{
					DebugMsg("搜索内存出现异常[%s]\n", e.what());
				}
				return 0;
			}
			static uint32_t SearchMemoryEx(const uint32_t uBeginAddress, const uint32_t uEndAddress, std::string lpszMasks, uint32_t uPos = 1)
			{
				return SearchMemory(uBeginAddress, uEndAddress, Cry::Text::Xor::Operate(lpszMasks), uPos);
			}
		private:
			Masks() = default;
			Masks(const Masks &) = default;
			Masks &operator=(const Masks &) = default;
		};
	};
};