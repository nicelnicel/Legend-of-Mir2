#include <Global>
#include <InterProcess/Cry.Signal.Service.h>
#include <Cry.FirstLication.h>
#include <SendCmd.pb.h>
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
			while (pData->length() > 0)
			{
				if (!uMsg)
				{
					if (!m_Service || pData->length() < HeadSize)
					{
						DLOG_TRACE << "Recv DataSize < HeardSize Error:" << m_Conn->remote_addr();
						return false;
					}
					uSize = pData->ReadInt32();
					uSize -= HeadSize;
					uMsg = pData->ReadInt32();
				}
				if (pData->size() < uSize)
				{
					DLOG_TRACE << "Recv DataSize < MessageSize:" << m_Conn->remote_addr();
					return false;
				}
				if (Action::lPUnknownInterfaceEx lpListener = m_Service->GetObjectInterface()->Get(0); (lpListener == nullptr ? lpListener = m_Service->GetObjectInterface()->Get("FirstLication") : lpListener))
				{
					try
					{
						if (!lpListener->OnSocketData(shared_from_this(), uMsg, pData->data(), uSize))
						{
							DLOG_TRACE << "发送数据失败";
							return false;
						}
					}
					catch (std::exception & e)
					{
						DebugMsg("%s\n", e.what());
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
			return true;
		}
		bool Work::Send(const uint32_t uMsg, const google::protobuf::Message &pData)
		{
			uint32_t len = (pData.ByteSize() + HeadSize);
			if(len >= HeadSize)
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
			return false;
		}
		bool Work::OnNotify(const uint32_t uMsg, const google::protobuf::Message *pData)
		{
			//DebugMsg("OnNotify -> 线程ID:%d\n", std::this_thread::get_id());
			return true;
		}
		///***********************************************************************************///
		///***********************************************************************************///
		///***********************************************************************************///
		NetworkEngineService::NetworkEngineService(const std::string& lpszAddress, const std::string& lpszFlags, uint32_t uThreadSize) : m_Server(m_EventLoop.loop(), lpszAddress, lpszFlags, uThreadSize)
		{
			m_Server.SetConnectionCallback(std::bind(&NetworkEngineService::OnConnection, this, std::placeholders::_1));
			m_Server.SetMessageCallback(std::bind(&NetworkEngineService::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
		}

		NetworkEngineService::~NetworkEngineService()
		{
			
		}
		bool NetworkEngineService::CreateService()
		{
			if (!m_Server.Init())
			{
				DLOG_WARN << "Initialize InterProcess Service Fail";
				return false;
			}
			if (!m_Server.Start())
			{
				DLOG_WARN << "Start InterProcess Service Fail";
				return false;
			}
			return m_EventLoop.Start();
		}
		bool NetworkEngineService::CancelService()
		{
			m_Server.Stop();
			m_EventLoop.Stop(true);
			return m_Server.IsStopped();
		}
		bool NetworkEngineService::OnNotify(const uint32_t uMsg, const google::protobuf::Message & pData)
		{
			DebugMsg("OnNotify -> 线程ID:%d\n", std::this_thread::get_id());
			if (auto Conn = this->GetWork(Buffer_Name); Conn)
			{
				std::lock_guard<std::mutex> Guard(m_Mutex);
				{
					return Conn->Send(0, pData);
				}
			}
			return false;
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
					//QObject::connect(m_QWindows.get(), &QWindows::FirstLication::PostNotify, this, &NetworkEngineService::OnNotify, Qt::DirectConnection);
					LOG_WARN << "Accept a new connection from:" << Conn->remote_addr() << " Conn:" << Conn->id() << " Thread:" << std::this_thread::get_id();
					DebugMsg("用户进入:%s 线程[%d]\n", Conn->remote_addr().c_str(), std::this_thread::get_id());
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
					//QObject::disconnect(m_QWindows.get(), &QWindows::FirstLication::PostNotify, this, &NetworkEngineService::OnNotify);
					LOG_WARN << "Disconnected from:" << Conn->remote_addr() << " Conn:" << Conn->id() << " Thread:" << std::this_thread::get_id();
					DebugMsg("用户离开:%s 线程[%d]\n", Conn->remote_addr().c_str(), std::this_thread::get_id());
				}
				else
				{
					Conn->Close();
				}
			}
		}
	};
};
