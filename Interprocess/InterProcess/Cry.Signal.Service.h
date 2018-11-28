#pragma once
#include <evpp/tcp_server.h>
#include <ServiceInterface/Cry.Signal.Interface.h>
#include <QObject>
namespace QWindows
{
	class FirstLication;
};
namespace Cry
{
	namespace Signal
	{
		class NetworkEngineService;
		class Work : public QObject, public std::enable_shared_from_this<Work>
		{
		public:
			Q_OBJECT
		public:
			Work(NetworkEngineService * Service, evpp::TCPConnPtr Conn, evpp::EventLoop * Loop);
			virtual ~Work() = default;
		public:
			virtual bool Receive(evpp::Buffer * pData) /*override*/;
			virtual bool Send(const uint32_t uMsg, const google::protobuf::Message & pData) /*override*/;
		public:
			virtual bool OnNotify(const uint32_t uMsg, const google::protobuf::Message *pData);
		private:
			evpp::TCPConnPtr										m_Conn;
			evpp::EventLoop*										m_Loop;
		private:
			NetworkEngineService*									m_Service;
		private:
			std::string												m_lpszBody;
		};
		
		class NetworkEngineService : public QObject, public ServiceInterface
		{
		public:
			Q_OBJECT
		public:
			NetworkEngineService(const std::string& lpszAddress, const std::string& lpszFlags, uint32_t uThreadSize);
			~NetworkEngineService();
		public:
			friend class ServiceInterface;
		public:
			std::shared_ptr<QWindows::FirstLication> & SetWindowsInterface(std::shared_ptr<QWindows::FirstLication> QWindows)
			{
				return m_QWindows = QWindows; m_QWindows;
			}
			virtual bool CreateService();
			virtual	bool CancelService();
			virtual void OnMessage(const evpp::TCPConnPtr & Conn, evpp::Buffer * Buffer) override;
			virtual void OnConnection(const evpp::TCPConnPtr & Conn) override;
		public:
			bool OnNotify(const uint32_t uMsg, const google::protobuf::Message & pData);
		private:
			evpp::EventLoopThread										m_EventLoop;
			evpp::TCPServer												m_Server;
		private:
			std::mutex													m_Mutex;
		private:
			std::shared_ptr<QWindows::FirstLication>					m_QWindows;
		};
	};
};