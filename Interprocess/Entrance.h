#pragma once
namespace Cry
{
	namespace Signal
	{
		class NetworkEngineService;
	}
}
class CryEntrance
{
public:
	CryEntrance() = default;
public:
	int32_t Run(HINSTANCE hInstance, int nCmdCount, Cry::Signal::NetworkEngineService * Service);
	void show()
	{
		m_Windwos->show();
	}
	void hide()
	{
		m_Windwos->hide();
	}
	~CryEntrance()
	{
		m_Windwos.reset();
	}
private:
	std::shared_ptr<QWindows::FirstLication>							m_Windwos;
};
static CryEntrance theapp;