#include <Global>
#include <Entrance.h>
#include <InterProcess/Cry.Signal.Client.h>
#include <Import/Cry.Glog.hpp>
#include <Import/Cry.Event.hpp>
#include <Import/Cry.Proto.hpp>
#include <Game/Initialize/Cry.Game.Initialize.h>
#include <Game/Cry.Game.Interface.h>
#include <Game/Utility/Cry.Game.Utility.h>
#include <Import/Memory/Cry.Game.Compare.hpp>
#include <StringXor.h>
bool CryEntrance::InitObjectInterface()
{
	// 服务器独立
	// 接口存储地址
	// 对象存储接口
	bool Sucess = true;
	if (m_InterfaceEx = std::make_shared<Cry::Action::Game::InterfaceEx>(m_DataBase); m_InterfaceEx)
	{
		Sucess &= m_Service->GetObjectInterface()->Add(0, new Cry::Action::Game::Utility(m_InterfaceEx));
	}
	return Sucess;
}
bool CryEntrance::InitializeNetworkService()
{
	// 只初始化一次
	if (!m_DataBase)
	{
		if (m_DataBase = std::make_shared<Cry::Base::DataBase>(); m_DataBase->Initialize())
		{
			if (m_Service = std::make_shared<Cry::Signal::NetworkEngineService>("127.0.0.1:9999", "Inter.Process.Client"); !this->InitObjectInterface() || !m_Service->CreateService())
			{
				return false;
			}
		}
	}
	return true;
}
void CryEntrance::ReleaseService()
{
	if (m_Service)
	{
		m_Service->CancelService();
		m_Service.reset();
		m_DataBase.reset();
		m_InterfaceEx.reset();
	}
}
LRESULT CALLBACK CryEntrance::GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPMSG lpMsg = reinterpret_cast<LPMSG>(lParam);
	if (wParam == PM_REMOVE)
	{
		if (!(HIBYTE(HIWORD(lpMsg->lParam)) & 0x40))
		{
			if (lpMsg->message == WM_USER + 9527)
			{
				if (m_Initialize)
				{
					m_Initialize = true;
					m_Status = true;
				}
				else
				{
					m_Initialize = this->InitializeNetworkService();
				}
			}
			if (m_Initialize)
			{
				if (lpMsg->message == WM_KEYDOWN || lpMsg->message == WM_SYSKEYDOWN)
				{
					if (lpMsg->wParam == VK_HOME)
					{
						if (m_Status)
						{
							m_Status = !m_Status;
						}
						else
						{
							m_Status = !m_Status;
						}
						DebugMsg("m_Status:%d\n", m_Status);
					}
				}
			}
			else
			{
				m_Initialize = this->InitializeNetworkService();
			}
		}
	}
	if (lpMsg->message == WM_USER + 9999 && lpMsg->wParam == 9527 && lpMsg->lParam == 1)
	{
		DebugMsg("主动卸载客户\n");
		this->ReleaseService();
	}
	if (lpMsg->message == WM_QUIT)
	{
		DebugMsg("被动卸载客户\n");
		this->ReleaseService();
		PostQuitMessage(0);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
LRESULT CALLBACK CryEntrance::InterFaceDll(int nCode, WPARAM wParam, LPARAM lParam)
{
	return theapp.GetMsgProc(nCode, wParam, lParam);
}
int main()
{
	google::InitGoogleLogging("Client");
	google::SetLogDestination(google::GLOG_INFO, "./Log/");
	google::InstallFailureSignalHandler();
	FLAGS_colorlogtostderr = true;
	FLAGS_stop_logging_if_full_disk = true;
	FLAGS_v = 3;
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);

	theapp.InitializeNetworkService();

	for (;;)
	{
		Sleep(100);
	}
	getchar();

	WSACleanup();
	google::ShutdownGoogleLogging();
	return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);
		google::InitGoogleLogging("Client");
		google::SetLogDestination(google::GLOG_INFO, "./Log/");
		google::InstallFailureSignalHandler();
		FLAGS_colorlogtostderr = true;
		FLAGS_stop_logging_if_full_disk = true;
		FLAGS_v = 3;
		WSADATA WSAData;
		WSAStartup(MAKEWORD(2, 2), &WSAData);
		break;
	}
    case DLL_THREAD_ATTACH:
	{
		DebugMsg("线程初始\n");
		break;
	}
    case DLL_THREAD_DETACH:
	{
		DebugMsg("线程销毁\n");
		break;
	}
    case DLL_PROCESS_DETACH:
	{
		WSACleanup();
		google::ShutdownGoogleLogging();
		DebugMsg("Dll卸载\n");
		break;
	}
	default: break;
    }
    return TRUE;
}