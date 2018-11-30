#include <Global>
#include <Game/Cry.Game.Interface.h>
#include <Game/Initialize/Cry.Game.Initialize.h>
namespace Cry
{
	namespace Action
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
			u32 Interface::GetPointer(std::string lpszString)
			{
				try
				{
					return CryVirtualQueryMemory(u32, CryVirtualQueryMemory(u32, m_DataBase->Get(lpszString)));
				}
				catch (std::string & lpszString)
				{
					DebugMsg("%s:%s\n", __FUNCTION__, lpszString.c_str());
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
			bool InterfaceEx::SendCmd(std::string lpszString)
			{
				CryVirtualQueryMemory(i8 *, m_Interface->GetPointer("\xAE\x79\xD1\x03\xB6\x05\xB5\x56\x00\x00")) = lpszString.data();
				return true;
			}
		};
	};
};