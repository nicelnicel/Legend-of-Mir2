#include <Global>
#include <ServiceInterface/Cry.Signal.Interface.h>
namespace Cry
{
	namespace Signal
	{
		ServiceInterface::ServiceInterface() : m_ObjectInterface(std::make_shared<Action::ObjectInterface>())
		{
			DebugMsg("¹¹Ôì\n");
		}
		ServiceInterface::~ServiceInterface()
		{
			this->ClearWork();
			m_ObjectInterface->Clear();
			m_ObjectInterface.reset();
		}
		bool ServiceInterface::AddWork(const uint64_t uConn, std::shared_ptr<Work> WorkPtr)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (std::begin(m_Work) == std::end(m_Work))
			{
				m_Work.insert({ uConn, WorkPtr });
				return true;
			}
			return false;
		}
		bool ServiceInterface::AddWork(const std::string & Name, std::shared_ptr<Work> WorkPtr)
		{
			std::lock_guard<std::mutex> guard(m_Name_Mutex);
			if (std::begin(m_Name_Work) == std::end(m_Name_Work))
			{
				m_Name_Work.insert({ Name, WorkPtr });
				return true;
			}
			return false;
		}
		std::shared_ptr<Work> ServiceInterface::GetWork(const uint64_t uConn)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_Work.find(uConn); list != std::end(m_Work))
			{
				return list->second;
			}
			return nullptr;
		}
		std::shared_ptr<Work> ServiceInterface::GetWork(const std::string & Name)
		{
			std::lock_guard<std::mutex> Guard(m_Name_Mutex);
			if (auto list = m_Name_Work.find(Name); list != std::end(m_Name_Work))
			{
				return list->second;
			}
			return nullptr;
		}
		bool ServiceInterface::DelWork(const uint64_t uConn)
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			if (auto list = m_Work.find(uConn); list != std::end(m_Work))
			{
				m_Work.erase(list);
				return true;
			}
			return false;
		}
		bool ServiceInterface::DelWork(const std::string & Name)
		{
			std::lock_guard<std::mutex> Guard(m_Name_Mutex);
			if (auto list = m_Name_Work.find(Name); list != std::end(m_Name_Work))
			{
				m_Name_Work.erase(list);
				return true;
			}
			return false;
		}
		void ServiceInterface::ClearWork()
		{
			std::lock_guard<std::mutex> Guard(m_Mutex);
			{
				for (auto list = std::begin(m_Work); list != std::end(m_Work);)
				{
					list->second.reset();
					list = m_Work.erase(list);
				}
			}
			m_Work.clear();
			std::lock_guard<std::mutex> Name_Guard(m_Name_Mutex);
			{
				for (auto list = std::begin(m_Name_Work); list != std::end(m_Name_Work);)
				{
					list->second.reset();
					list = m_Name_Work.erase(list);
				}
			}
			m_Name_Work.clear();
		}
	};
};