#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <event2/event.h>
#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>
#include <evpp/logging.h>
int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);

	google::InitGoogleLogging("Server");
	google::SetLogDestination(google::GLOG_WARNING, "./Log/");
	//google::InstallFailureSignalHandler();
	FLAGS_logtostderr = false;
	FLAGS_colorlogtostderr = false;
	FLAGS_v = 3;
	FLAGS_stop_logging_if_full_disk = true;

	LOG_WARN << "开始初始化服务器";

	std::string addr = "0.0.0.0:9099";
	int thread_num = 4;
	evpp::EventLoopThread loop;
	evpp::TCPServer server(loop.loop(), addr, "TCPEchoServer", thread_num);
	server.SetMessageCallback([](const evpp::TCPConnPtr& conn,
		evpp::Buffer* msg) {
		conn->Send(msg);
	});
	server.SetConnectionCallback([](const evpp::TCPConnPtr& conn) {
		if (conn->IsConnected()) {
			LOG_INFO << "A new connection from " << conn->remote_addr();
		}
		else {
			LOG_INFO << "Lost the connection from " << conn->remote_addr();
		}
	});
	server.Init();
	server.Start();
	loop.Start();

	server.Stop();
	loop.Stop();
	
	google::ShutdownGoogleLogging();
	//WSACleanup();
	getchar();
	return 0;
}