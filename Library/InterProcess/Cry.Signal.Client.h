#pragma once
#include <evpp/event_loop_thread_pool.h>
#include <evpp/tcp_client.h>
#include <ServiceInterface/Cry.Signal.Interface.h>
namespace Cry
{
	namespace Signal
	{
		class NetworkEngineService;
		class Work : public std::enable_shared_from_this<Work>
		{
		public:
			Work(NetworkEngineService * Service, evpp::TCPConnPtr Conn, evpp::EventLoop* Loop);
			virtual ~Work() = default;
		public:
			virtual bool Receive(evpp::Buffer * pData);
			virtual bool Send(const uint32_t uMsg, const google::protobuf::Message &pData);
		private:
			evpp::TCPConnPtr										m_Conn;
			evpp::EventLoop*										m_Loop;
		private:
			NetworkEngineService*									m_Service;
		private:
			std::string												m_lpszBody;
		};

		class NetworkEngineService : public ServiceInterface
		{
		public:
			NetworkEngineService(const std::string& lpszAddress = std::string("127.0.0.1:9999"), const std::string& lpszFlags = std::string("Inter.Process.Client"));
			~NetworkEngineService();
		public:
			friend class ServiceInterface;
		public:
			virtual bool CreateService();
			virtual bool CancelService();
			virtual void OnMessage(const evpp::TCPConnPtr & Conn, evpp::Buffer * Buffer) override;
			virtual void OnConnection(const evpp::TCPConnPtr & Conn) override;
		private:
			evpp::EventLoopThread										m_EventLoop;
			evpp::TCPClient												m_Client;
		};
	};
};