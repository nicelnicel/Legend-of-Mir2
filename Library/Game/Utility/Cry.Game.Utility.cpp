#include <Global>
#include <Game/Utility/Cry.Game.Utility.h>
#include <Interprocess/Cry.Signal.Client.h>
#include <SendCmd.pb.h>
#include <Import/Memory/Cry.Game.Compare.hpp>
#include <Game/Cry.Game.Interface.h>
#include <Exception/Cry.Exception.hpp>
namespace Cry
{
	namespace Action
	{
		Utility::Utility(std::shared_ptr<Cry::Game::InterfaceEx> & Interface) : m_Interface(Interface)
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
			if (!Req.ParseFromArray(pData, uSize))
			{
				throw Cry::Exception("解析数据包出现严重错误");
			}
			Resp.clear_status();
			Resp.set_status(false);
			if (m_Interface->SendCmd((Cry::Encrypt::Xor::Operate(Req.content()).data())))
			{
				DebugMsg("来自客户端的消息：%s\n", Cry::Encrypt::Xor::Operate(Req.content()).c_str());
				return pWork->Send(0, Resp);
			}
			return false;
		}
	};
};