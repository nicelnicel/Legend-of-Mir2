#include <Global>
#include <Game/Cry.Game.Interface.h>
#include <Game/Initialize/Cry.Game.Initialize.h>
#include <StringXor.h>
#include <Game/Exception/Cry.Game.Exception.hpp>
namespace Cry
{
	namespace Game
	{
		Interface::Interface(std::shared_ptr<Base::DataBase> & DataBase) : m_DataBase(DataBase)
		{

		}
		Interface::~Interface()
		{
			m_DataBase = nullptr;
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
			catch(Cry::Game::Exception & e)
			{
				DebugMsg("%s:%s\n", __FUNCTION__, e.Info().c_str());
			}
			return 0;
		}
		InterfaceEx::InterfaceEx(std::shared_ptr<Base::DataBase> & DataBase) : m_Interface(std::make_shared<Game::Interface>(DataBase)), m_DataBase(DataBase)
		{

		}
		InterfaceEx::~InterfaceEx()
		{
			m_DataBase = nullptr;
			m_Interface.reset();
		}
		u32 InterfaceEx::ExceptionFunction(u32 dwExceptionCode)
		{
			u32 ExceptionCode = EXCEPTION_CONTINUE_SEARCH;
			switch (dwExceptionCode)
			{
			case EXCEPTION_INVALID_DISPOSITION:
			case EXCEPTION_BREAKPOINT:
			case EXCEPTION_ACCESS_VIOLATION:
			case EXCEPTION_FLT_STACK_CHECK:
			case EXCEPTION_STACK_OVERFLOW: ExceptionCode = EXCEPTION_EXECUTE_HANDLER; break;
			default: break;
			}
			return ExceptionCode;
		}
		bool InterfaceEx::SendCmd(lPCString lpszString)
		{
			__try
			{
				// 发言
				CryVirtualQueryMemory(lPCString, m_Interface->GetPointer("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00")) = lpszString;

				// 结束
				CryVirtualQueryMemory(lPCString, m_Interface->GetPointer("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00")) = 0;
			}
			__except (Cry::Game::Exception::ExceptionHandler(GetExceptionCode()))
			{
				DebugMsg("Structured Exception Handling -> %s\n", __FUNCTION__);
			}
			return true;
		}
	};
};