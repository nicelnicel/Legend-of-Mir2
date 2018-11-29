#pragma once
#include <Global>
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
			/// 代码来源：https://github.com/learn-more/findpattern-bench/blob/master/patterns/learn_more.h
			/// 修复问题：特征码末尾一个结束符'\0'导致内存搜索失败的情况。
			/// 优化性能：跳过int3断点。
			/// 优化视觉：读内存以宏代替，编译器会自动展开。
			static u32 SearchMemory(const u32 uBeginAddress, const u32 uEndAddress, std::string lpszMasks, u32 uPos)
			{
				const char*		pbSearchBuffer		= lpszMasks.data();
				u8*				uResult				= 0;
				u32				Pos					= 0;
				ulong32			lpflOldProtect		= 0;
				ulong32			lpflNewProtect		= 0;
				bool			bSucess				= false;
				u32				uProtceSize			= (uEndAddress - uBeginAddress);
				try
				{
					if (VirtualProtectEx(INVALID_HANDLE_VALUE, reinterpret_cast<LPVOID>(uBeginAddress), uProtceSize, PAGE_EXECUTE_READWRITE, &lpflNewProtect))
					{
						for (u8 * pCur = reinterpret_cast<u8*>(uBeginAddress); pCur < reinterpret_cast<u8*>(uEndAddress); ++pCur)
						{
							if (*pCur != 0xCC && CryVirtualQueryMemory(uint8_t, pbSearchBuffer) == ((u8)'\?') || *pCur == getByte(pbSearchBuffer))
							{
								if (!uResult)
								{
									uResult = pCur;
								}

								if (pbSearchBuffer += (CryVirtualQueryMemory(u16, pbSearchBuffer) == ((u16)'\?\?') || CryVirtualQueryMemory(uint8_t, pbSearchBuffer) != ((u8)'\?')) ? 3 : 2; (!*pbSearchBuffer) || (!*(pbSearchBuffer - 1)) || (!*(pbSearchBuffer + 1)))
								{
									if (++Pos == uPos)
									{
										break;
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
						if (!VirtualProtectEx(INVALID_HANDLE_VALUE, reinterpret_cast<LPVOID>(uBeginAddress), uProtceSize, lpflNewProtect, &lpflOldProtect))
						{
							DebugMsg("内存属性重置出现错误:%d\n", GetLastError());
							return 0;
						}
					}
				}
				catch (std::exception & e)
				{
					DebugMsg("搜索内存出现异常[%s]\n", e.what());
				}
				return reinterpret_cast<u32>(uResult);
			}
			static u32 SearchMemoryEx(const u32 uBeginAddress, const u32 uEndAddress, std::string lpszMasks, u32 uPos = 1)
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