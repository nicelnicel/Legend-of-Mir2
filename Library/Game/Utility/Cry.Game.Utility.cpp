#include <Standard>
#include <Game/Utility/Cry.Game.Utility.h>
#include <Interprocess/Cry.Signal.Client.h>
#include <SendCmd.pb.h>
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
			bool Utility::OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize)
			{
				SocketData::CmdRequest Req;
				SocketData::CmdResponse Resp;
				if (!Req.ParsePartialFromArray(pData, uSize))
				{
					return false;
				}
				Resp.clear_status();
				Resp.set_status(false);
				DebugMsg("服务消息 %s\n", Req.content().c_str());
				return pWork->Send(0, Resp);
				//INADDR_ANY
			}
		};
	};
};