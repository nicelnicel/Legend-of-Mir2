#pragma once
namespace Cry
{
	namespace Signal
	{
		class NetworkEngineService;
	};
	namespace Action
	{
		namespace Game
		{
			class InterfaceEx;
		};
	};
	namespace Base
	{
		class DataBase;
	}
};
class CryEntrance
{
public:
	CryEntrance()
	{
		m_Initialize = false;
		m_Status = false;
	}
	~CryEntrance()
	{
		this->ReleaseService();
	}
	void ReleaseService();
public:
	std::shared_ptr<Cry::Signal::NetworkEngineService> GetService()
	{
		return m_Service;
	}
	bool InitObjectInterface();
	bool InitializeNetworkService();
	LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK InterFaceDll(int nCode, WPARAM wParam, LPARAM lParam);
public:
	HMODULE														m_hInstance;
private:
	bool														m_Initialize;
	bool														m_Status;
private:
	std::shared_ptr<Cry::Signal::NetworkEngineService>			m_Service;
	std::shared_ptr<Cry::Base::DataBase>						m_DataBase;
	std::shared_ptr<Cry::Action::Game::InterfaceEx>				m_InterfaceEx;
};
static CryEntrance theapp;