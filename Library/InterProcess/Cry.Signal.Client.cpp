#include <Global>
#include <InterProcess/Cry.Signal.Client.h>
namespace Cry
{
	namespace Signal
	{
		Work::Work(NetworkEngineService * Service, evpp::TCPConnPtr Conn, evpp::EventLoop* Loop)
		{
			m_Service = Service;
			m_Conn = Conn;
			m_Loop = Loop;
		}
		bool Work::Receive(evpp::Buffer * pData)
		{
			uint32_t uMsg = 0, uSize = 0;
			WorkLeave Leave(pData);
			{
				while (pData->length() > 0)
				{
					if (!uMsg)
					{
						if (!m_Service || pData->length() < HeadSize)
						{
							DLOG_TRACE << "不完整的数据包";
							return false;
						}
						uSize = pData->ReadInt32();
						uSize -= HeadSize;
						uMsg = pData->ReadInt32();
					}
					if (pData->size() < uSize)
					{
						DLOG_TRACE << "无法解析数据包";
						return false;
					}
					if (Action::lPUnknownInterfaceEx lpListener = m_Service->GetObjectInterface()->Get(0); (lpListener == nullptr ? lpListener = m_Service->GetObjectInterface()->Get("123") : lpListener))
					{
						try
						{
							if (!lpListener->OnSocketData(shared_from_this(), uMsg, pData->data(), uSize))
							{
								DLOG_TRACE << "发送数据失败";
								return false;
							}
						}
						catch (std::string & lpszString)
						{
							DebugMsg("%s\n", lpszString.c_str());
							return false;
						}
					}
					else
					{
						DLOG_TRACE << "Exec lpListener = nullptr:" << m_Conn->remote_addr();
						return false;
					}
					pData->Skip(uSize);
					uMsg = 0;
				}
			}
			return true;
		}
		bool Work::Send(const uint32_t uMsg, const google::protobuf::Message &pData)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			{
				uint32_t len = (pData.ByteSize() + HeadSize);
				if (len >= HeadSize)
				{
					if (m_lpszBody.capacity() < len)
					{
						m_lpszBody.resize(len);
					}

					*reinterpret_cast<uint32_t *>(const_cast<char *>(m_lpszBody.data())) = htonl(len);
					*reinterpret_cast<uint32_t *>(const_cast<char *>(m_lpszBody.data()) + sizeof(uint32_t)) = htonl(uMsg);

					if (pData.SerializePartialToArray(const_cast<char *>(m_lpszBody.data()) + HeadSize, pData.ByteSize()))
					{
						m_Conn->Send(m_lpszBody.data(), len);
						return true;
					}
				}
			}
			return false;
		}

		NetworkEngineService::NetworkEngineService(const std::string& lpszAddress, const std::string& lpszFlags) : m_Client(m_EventLoop.loop(), lpszAddress, lpszFlags)
		{
			m_Client.SetConnectionCallback(std::bind(&NetworkEngineService::OnConnection, this, std::placeholders::_1));
			m_Client.SetMessageCallback(std::bind(&NetworkEngineService::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
		}
		NetworkEngineService::~NetworkEngineService()
		{
			
		}
		bool NetworkEngineService::CreateService()
		{
			m_Client.Connect();
			return m_EventLoop.Start();
		}
		bool NetworkEngineService::CancelService()
		{
			m_Client.Disconnect();
			m_EventLoop.Stop(true);
			return true;
		}
		void NetworkEngineService::OnMessage(const evpp::TCPConnPtr & Conn, evpp::Buffer * Buffer)
		{
			if (std::shared_ptr<Work> lpWork = this->GetWork(Buffer_Name); lpWork)
			{
				if (!lpWork->Receive(Buffer))
				{
					LOG_WARN << "Disconnected from:" << Conn->remote_addr() << " Conn:" << Conn->id() << " Thread:" << std::this_thread::get_id();
					//Conn->Close();
				}
			}
		}
		void NetworkEngineService::OnConnection(const evpp::TCPConnPtr & Conn)
		{
			if (Conn->IsConnected())
			{
				if (this->AddWork(Buffer_Name, std::make_shared<Work>(this, Conn, Conn->loop())))
				{
					DebugMsg("与服务器连接成功:%s\n", Conn->remote_addr().c_str());
					//Conn->Send("123");
				}
				else
				{
					Conn->Close();
				}
			}
			else
			{
				if (this->DelWork(Buffer_Name))
				{
					DebugMsg("与服务器断开连接:%s\n", Conn->remote_addr().c_str());
				}
			}
		}
	};
};
