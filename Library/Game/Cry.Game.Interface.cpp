#include <Global>
#include <Game/Cry.Game.Interface.h>
#include <Game/Initialize/Cry.Game.Initialize.h>
#include <StringXor.h>
#include <Exception/Cry.Exception.hpp>
#include <Import/Detour/Cry.DetourEngine.hpp>
namespace Cry
{
	namespace Game
	{
		Interface::Interface(std::shared_ptr<Base::DataBase> & DataBase) : m_DataBase(DataBase)
		{

		}
		Interface::~Interface()
		{
			
		}
		u32 Interface::GetPointer(lPCString lpszString)
		{
			try
			{
				return CryVirtualQueryMemory(u32, m_DataBase->Get(lpszString));
			}
			catch (std::string & lpszExceptionString)
			{
				DebugMsg("%s:%s\n", __FUNCTION__, lpszExceptionString.c_str());
			}
			catch(Cry::Exception & ex)
			{
				DebugMsg("%s:%s\n", __FUNCTION__, ex.lpszString());
			}
			return 0;
		}
		InterfaceEx::InterfaceEx(std::shared_ptr<Base::DataBase> & DataBase) : m_Interface(std::make_shared<Game::Interface>(DataBase)), m_DataBase(DataBase), m_DetourEngine(std::make_unique<DetourEngine>())
		{

		}
		InterfaceEx::~InterfaceEx()
		{
			m_DataBase = nullptr;
			m_Interface.reset();
			m_DetourEngine.reset();
		}
		bool InterfaceEx::SendCmd(lPString lpszString)
		{
			__try
			{
				// 发言
				CryVirtualQueryMemory(lPCString, m_Interface->GetPointer("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00")) = lpszString;

				// 结束
				CryVirtualQueryMemory(lPCString, m_Interface->GetPointer("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00")) = 0;
			}
			__except (Cry::Exception::ExceptionHandler(GetExceptionCode()))
			{
				DebugMsg("Structured Exception Handling -> %s\n", __FUNCTION__);
			}
			return true;
		}
	};
};