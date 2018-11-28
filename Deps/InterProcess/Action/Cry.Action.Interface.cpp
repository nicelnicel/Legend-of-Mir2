#include <Global>
#include <Action/Cry.Action.Interface.h>
namespace Cry
{
	namespace Action
	{
		ObjectInterface::ObjectInterface()
		{

		}
		ObjectInterface::~ObjectInterface()
		{
			this->Clear();
		}
		bool ObjectInterface::Add(uint32_t uMsg, std::shared_ptr<Action::UnknownInterfaceEx> Object)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_Object.find(uMsg); list == std::end(m_Object))
			{
				m_Object.insert(std::make_pair(uMsg, std::move(std::make_any<lPUnknownInterfaceEx>(Object.get()))));
				return true;
			}
			return false;
		}

		bool ObjectInterface::Add(uint32_t uMsg, lPUnknownInterfaceEx Object)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_Object.find(uMsg); list == std::end(m_Object))
			{
				m_Object.insert(std::make_pair(uMsg, Object));
				return true;
			}
			return false;
		}
		lPUnknownInterfaceEx ObjectInterface::Get(uint32_t uMsg)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_Object.find(uMsg); list != std::end(m_Object))
			{
				return std::any_cast<lPUnknownInterfaceEx>(list->second);
			}
			return nullptr;
		}
		bool ObjectInterface::Add(std::string lpszFlags, std::shared_ptr<Action::UnknownInterfaceEx> Object)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_ObjectEx.find(lpszFlags); list == std::end(m_ObjectEx))
			{
				m_ObjectEx.insert(std::make_pair(lpszFlags, std::move(std::make_any<lPUnknownInterfaceEx>(Object.get()))));
				return true;
			}
			return false;
		}
		bool ObjectInterface::Add(std::string lpszFlags, lPUnknownInterfaceEx Object)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_ObjectEx.find(lpszFlags); list == std::end(m_ObjectEx))
			{
				m_ObjectEx.insert(std::make_pair(lpszFlags, std::move(std::make_any<lPUnknownInterfaceEx>(Object))));
				return true;
			}
			return false;
		}

		lPUnknownInterfaceEx ObjectInterface::Get(std::string lpszFlags)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_ObjectEx.find(lpszFlags); list != std::end(m_ObjectEx))
			{
				return std::any_cast<lPUnknownInterfaceEx>(list->second);
			}
			return nullptr;
		}

		void ObjectInterface::Clear()
		{
			try
			{
				std::lock_guard<std::mutex> Guard(m_Mutex);
				{
					for (auto list = std::begin(m_Object); list != std::end(m_Object);)
					{
						delete std::any_cast<lPUnknownInterfaceEx>(list->second);
						list->second.reset();
						list = m_Object.erase(list);
					}
					m_Object.clear();
				}
				std::lock_guard<std::mutex> GuardEx(m_MutexEx);
				{
					for (auto list = std::begin(m_ObjectEx); list != std::end(m_ObjectEx);)
					{
						list->second.reset();
						list = m_ObjectEx.erase(list);
					}
					m_ObjectEx.clear();
				}
			}
			catch (std::exception e)
			{
				DebugMsg("ObjectInterface::Clear Error\n");
			}
		}
	};
};