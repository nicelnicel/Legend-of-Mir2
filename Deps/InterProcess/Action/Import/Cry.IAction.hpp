#pragma once
#include <Standard>
#include <Cry.Import.Action.h>
#include <memory>
#include <any>
namespace Cry
{
	namespace Signal
	{
		class Work;
	}
	namespace Action
	{
		// 分发窗口消息
		class DispatcherInterface
		{
		public:
			virtual ~DispatcherInterface() = default;
		public:
			virtual LRESULT OnMessage(int nCode, WPARAM wParam, LPARAM lParam) { return 0; };
		protected:
			DispatcherInterface() = default;
			DispatcherInterface(const DispatcherInterface &) = default;
			DispatcherInterface &operator=(const DispatcherInterface &) = default;
		};
		typedef DispatcherInterface* lPDispatcherInterface;

		// 分发网络消息
		class UnknownInterfaceEx : public DispatcherInterface
		{
		public:
			virtual ~UnknownInterfaceEx() = default;
		public:
			virtual bool OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize) = 0;
		protected:
			UnknownInterfaceEx() = default;
			UnknownInterfaceEx(const UnknownInterfaceEx &) = default;
			UnknownInterfaceEx &operator=(const UnknownInterfaceEx &) = default;
		};
		typedef UnknownInterfaceEx* lPUnknownInterfaceEx;
	}
}