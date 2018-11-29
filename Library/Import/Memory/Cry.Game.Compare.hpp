#pragma once
#include <cstdint>
#include <Helper>
namespace Cry
{
	namespace Action
	{
		namespace Game
		{
			namespace Memory
			{
				class Masks
				{
				public:
					virtual ~Masks() = default;
				public:
					static PBYTE findPattern(const PBYTE rangeStart, const PBYTE rangeEnd, const char* pattern)
					{
						const unsigned char* pat = reinterpret_cast<const unsigned char*>(pattern);
						PBYTE firstMatch = 0;
						for (PBYTE pCur = rangeStart; pCur < rangeEnd; ++pCur) {
							if (*(PBYTE)pat == (BYTE)'\?' || *pCur == getByte(pat)) {
								if (!firstMatch) {
									firstMatch = pCur;
								}
								pat += (*(PWORD)pat == (WORD)'\?\?' || *(PBYTE)pat != (BYTE)'\?') ? 3 : 2;
								if (!*pat) {
									return firstMatch;
								}
							}
							else if (firstMatch) {
								pCur = firstMatch;
								pat = reinterpret_cast<const unsigned char*>(pattern);
								firstMatch = 0;
							}
						}
						return NULL;
					}

					static uint32_t SearchMemory(const uint32_t uBeginAddress, const uint32_t uEndAddress, const char * lpszMasks, uint32_t uPos = 1) noexcept
					{
						const char * pbSearchBuffer = lpszMasks;
						uint8_t * uResult = 0;
						uint32_t Pos = 0;
						for (uint8_t * pCur = reinterpret_cast<uint8_t*>(uBeginAddress); pCur < reinterpret_cast<uint8_t*>(uEndAddress); ++pCur)
						{
							if (CryVirtualQueryMemory(uint16_t, pbSearchBuffer) == (uint16_t)'\?\?' || CryVirtualQueryMemory(uint8_t, pbSearchBuffer) == (uint8_t)'\?' || *pCur == getByte(pbSearchBuffer))
							{
								if (!uResult)
								{
									uResult = pCur;
								}
								if (pbSearchBuffer += (CryVirtualQueryMemory(uint16_t, pbSearchBuffer) == ((uint16_t)'\?\?') || CryVirtualQueryMemory(uint8_t, pbSearchBuffer) != ((uint8_t)'\?')) ? 3 : 2; (!*pbSearchBuffer))
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
								pbSearchBuffer = lpszMasks;
								uResult = 0;
							}
						}
						return 0;
					}
				private:
					Masks() = default;
					Masks(const Masks &) = default;
					Masks &operator=(const Masks &) = default;
				};
			};
		};
	}
};