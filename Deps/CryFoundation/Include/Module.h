#if !defined(CRY_MODULE_H)
#define CRY_MODULE_H
#pragma once
#include <Foundation.h>
namespace Cry
{
	namespace Kernel
	{
		typedef struct _TEB *PTEB;
		class FunctionExport Module
		{
		public:
			Module() = delete;
		public:
			static PTEB GetContextTeb();
			static bool HideModuleByHandle(HMODULE hInstance);
			static bool HideModuleByHandleEx(HMODULE hInstance, HANDLE hHandle = GetCurrentProcess());
			static bool HideBreakpoint(HANDLE hThread = GetCurrentThread());
			static bool EnumeModuleInfo(HANDLE hHandle = GetCurrentProcess());
			static bool GetModuleFullPath(HMODULE hInstance, char* lpFilename);
		protected:
			Module(const Module&) = delete;
			Module& operator = (const Module&) = delete;
		};
		//extern char lpFiledir[MAX_PATH];
	}
}
#endif