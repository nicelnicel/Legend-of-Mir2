#include <Global>
#include <Game/Utility/Cry.Game.Utility.h>
#include <Interprocess/Cry.Signal.Client.h>
#include <SendCmd.pb.h>
#include <Import/Memory/Cry.Game.Compare.hpp>
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

				std::string lpszText = Text::Xor::Operate("\x22\xF8\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x22\x9D\x50\x8B\x40\x85\x22\x9D\x50\x85\x40\xFB\x26\x9D\x5F\x82\x40\x82\x5F\x9D\x58\xFF\x40\xF9\x50\x00\x00");

				u32 Test = Cry::Memory::Masks::SearchMemoryEx(0x516000, 0x516FFF, "\x22\xF8\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x22\x9D\x50\x8B\x40\x85\x22\x9D\x50\x85\x40\xFB\x26\x9D\x5F\x82\x40\x82\x5F\x9D\x58\xFF\x40\xF9\x50\x00\x00");
				
				
				DebugMsg("解密：%s 地址：%p\n", lpszText.c_str(), Test);
				return pWork->Send(0, Resp);
			}
		};
	};
};