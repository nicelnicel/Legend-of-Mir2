#include <Global>
#include <Game/Utility/Cry.Game.Utility.h>
#include <Interprocess/Cry.Signal.Client.h>
#include <SendCmd.pb.h>
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
				uint32_t uStarTimer = GetTickCount();
				uint32_t uResult = Cry::Action::Game::Memory::Masks::SearchMemoryEx(0x401000, 0x5F9FFF, "\x58\xFF\x40\xF9\x53\x9D\x25\x85\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x54\x9D\x23\x8D\x40\x8A\x54\x9D\x5F\x82\x40\x85\x50\x9D\x22\xFF\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x8D\x50");
				DebugMsg("搜索结果:%08X 总时:%d毫秒\r\n", uResult, GetTickCount() - uStarTimer);
				return pWork->Send(0, Resp);
			}
		};
	};
};