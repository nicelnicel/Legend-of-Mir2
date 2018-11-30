#pragma once
#include <Action/Import/Cry.IAction.hpp>
namespace Cry
{
	namespace Game
	{
		class InterfaceEx;
	};
	namespace Signal
	{
		class Work;
	};
	namespace Action
	{
		class Utility : public UnknownInterfaceEx
		{
		public:
			Utility(std::shared_ptr<Cry::Game::InterfaceEx> & Interface);
			~Utility();
		public:
			virtual bool OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize) override;
		private:
			std::shared_ptr<Cry::Game::InterfaceEx>									m_Interface;
		};
	};
};