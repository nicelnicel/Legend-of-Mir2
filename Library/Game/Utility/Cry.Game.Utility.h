#pragma once
#include <Action/Import/Cry.IAction.hpp>
namespace Cry
{
	namespace Signal
	{
		class Work;
	};
	namespace Action
	{
		namespace Game
		{
			class Utility : public UnknownInterfaceEx
			{
			public:
				Utility();
				~Utility();
			public:
				virtual bool OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize) override;
			};
		};
	};
};