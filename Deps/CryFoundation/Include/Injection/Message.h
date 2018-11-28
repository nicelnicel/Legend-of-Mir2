#if !defined(CRY_MESSAGE_H)
#define CRY_MESSAGE_H
#pragma once
#include <Foundation.h>
#include <Kernel.h>
namespace Cry
{
	namespace Kernel
	{
		class Message
		{
		public:
			Message() = delete;
			static bool InstallWindowsMessageEx(HWND hWnd, LPCTSTR lpLibFileName, LPCTSTR lpProcName, DWORD dwFlags = DONT_RESOLVE_DLL_REFERENCES | LOAD_IGNORE_CODE_AUTHZ_LEVEL);
			static bool UninstallWindowsMessageEx();
			static DWORD GetProcessId();
			static DWORD GetThreadId();
		protected:
			Message(const Message&) = delete;
			Message& operator = (const Message&) = delete;
		};

	};
};
#endif