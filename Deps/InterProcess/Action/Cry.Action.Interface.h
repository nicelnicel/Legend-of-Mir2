#pragma once
#include <cstdint>
#include <unordered_map>
#include <mutex>
#include <Action/Import/Cry.IAction.hpp>
namespace Cry
{
	namespace Action
	{
		namespace Game
		{
			class Utility;
		}
		class ObjectInterface
		{
		public:
			ObjectInterface();
			~ObjectInterface();
		public:
			template<typename _Ty, typename ..._Types>
			bool Add(std::string lpszFlags, _Types&&... _Args)
			{
				std::lock_guard<std::mutex> Guard(m_Mutex);
				if (auto list = m_ObjectEx.find(lpszFlags); list == std::end(m_ObjectEx))
				{
					m_ObjectEx.insert(std::make_pair(lpszFlags, std::make_shared<std::any>(std::move(std::make_any<_Ty>(std::forward<_Types>(_Args)...)))));
					return true;
				}
				return false;
			}
			bool Add(uint32_t uMsg, std::shared_ptr<Action::UnknownInterfaceEx> Object);
			bool Add(uint32_t uMsg, lPUnknownInterfaceEx Object);
			lPUnknownInterfaceEx Get(uint32_t uMsg);

			bool Add(std::string lpszFlags, std::shared_ptr<Action::UnknownInterfaceEx> Object);
			bool Add(std::string lpszFlags, lPUnknownInterfaceEx Object);
			lPUnknownInterfaceEx Get(std::string lpszFlags);

			//std::string lpszFlags
			void Clear();
		protected:
			std::mutex														m_Mutex;
			std::mutex														m_MutexEx;
			std::unordered_map<uint32_t, std::any>							m_Object;
			std::unordered_map<std::string, std::any>						m_ObjectEx;
		};

		typedef ObjectInterface* lPObjectInterface;
	};
};