#pragma once
#include <memory>
#include <string>
namespace Cry
{
	class DetourEngine;
	namespace Base
	{
		class DataBase;
	};
	namespace Game
	{
		class Interface
		{
		public:
			Interface(std::shared_ptr<Base::DataBase> & DataBase);
			~Interface();
		public:
			u32 GetPointer(lPCString lpszString);
		private:
			std::shared_ptr<Base::DataBase>							m_DataBase;
		protected:
			Interface() = default;
			Interface(const Interface &) = default;
			Interface &operator=(const Interface &) = default;
		};

		class InterfaceEx
		{
		public:
			InterfaceEx(std::shared_ptr<Base::DataBase> & DataBase);
			~InterfaceEx();
			bool SendCmd(lPString lpszString);
		private:
			std::shared_ptr<Base::DataBase>							m_DataBase;
			std::shared_ptr<Game::Interface>						m_Interface;
			std::shared_ptr<DetourEngine>							m_DetourEngine;
		protected:
			InterfaceEx() = default;
			InterfaceEx(const InterfaceEx &) = default;
			InterfaceEx &operator=(const InterfaceEx &) = default;
		};
	};
};