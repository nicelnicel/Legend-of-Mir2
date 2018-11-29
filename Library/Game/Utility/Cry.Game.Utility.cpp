#include <Global>
#include <Game/Utility/Cry.Game.Utility.h>
#include <Interprocess/Cry.Signal.Client.h>
#include <SendCmd.pb.h>
#include <Import/Memory/Cry.Game.Compare.hpp>
#include <StringXor.h>
namespace Cry
{
	namespace Action
	{
		namespace Game
		{
			Utility::Utility()
			{

			}
			Utility::~Utility()
			{

			}
			/* INADDR_ANY */
			bool Utility::OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize)
			{
				SocketData::CmdRequest Req;
				SocketData::CmdResponse Resp;
				if (!Req.ParsePartialFromArray(pData, uSize))
				{
					throw std::string("解析数据包出现严重错误");
				}
				Resp.clear_status();
				Resp.set_status(false);

				static char lpszMask[] = "8B D3 E8 ?? ?? ?? ?? 84 C0 74 ?? 80 BB ?? ?? ?? ?? 00";
				DebugMsg("静态变量：%s\n", lpszMask);
				
				std::string lpszDestination = Cry::Text::Xor::Operate("\x58\xFF\x40\xF9\x53\x9D\x25\x85\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x54\x9D\x23\x8D\x40\x8A\x54\x9D\x5F\x82\x40\x85\x50\x9D\x22\xFF\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x8D\x50");
				DebugMsg("动态变量：%s\n", lpszDestination.c_str());

				if (!strcmp(lpszDestination.c_str(), lpszMask))
				{
					DebugMsg("完全相同\n");

					auto uAddress1 = Cry::Action::Game::Memory::Masks::SearchMemory(0x5F9000, 0x5F9FFF, lpszMask);
					DebugMsg("静态变量 搜索结果:%08X\r\n", uAddress1);

					auto uAddress2 = Cry::Action::Game::Memory::Masks::SearchMemory(0x5F9000, 0x5F9FFF, lpszDestination.c_str());
					DebugMsg("动态变量 搜索结果:%08X\r\n", uAddress2);
				}
				return pWork->Send(0, Resp);
			}
		};
	};
};