#include <Global>
#include <Entrance.h>
#include <InterProcess/Cry.Signal.Client.h>
#include <Import/Cry.Glog.hpp>
#include <Import/Cry.Event.hpp>
#include <Import/Cry.Proto.hpp>
#include <Game/Utility/Cry.Game.Utility.h>
#include <Import/Memory/Cry.Game.Compare.hpp>
#include <StringXor.h>
bool CryEntrance::InitObjectInterface()
{
	bool Sucess = true;
	DebugMsg("初始化全部对象\n");
	Sucess &= m_Service->GetObjectInterface()->Add(0, new Cry::Action::Game::Utility);
	return Sucess;
}
bool CryEntrance::InitializeNetworkService()
{
	if (m_Service = std::make_shared<Cry::Signal::NetworkEngineService>("127.0.0.1:9999", "Inter.Process.Client"); this->InitObjectInterface())
	{
		return m_Service->CreateService();
	}
	return false;
}
void CryEntrance::ReleaseService()
{
	if (m_Service)
	{
		m_Service->CancelService();
		m_Service.reset();
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