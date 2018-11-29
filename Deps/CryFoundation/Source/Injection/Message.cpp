#include  <Injection/Message.h>
namespace Cry
{
	namespace Kernel
	{
		static HHOOK lpMsgHandle;
		static DWORD lpdwProcessId;
		static DWORD dwThreadId;

		bool Message::InstallWindowsMessageEx(HWND hWnd, LPCTSTR lpLibFileName, LPCTSTR lpProcName, DWORD dwFlags)
		{
			if (dwThreadId = GetWindowThreadProcessId(hWnd, &lpdwProcessId); dwThreadId && lpdwProcessId)
			{
				if (HINSTANCE hInst = LoadLibraryEx(lpLibFileName, NULL, dwFlags); hInst)
				{
					if (HOOKPROC lpfn = reinterpret_cast<HOOKPROC>(GetProcAddress(hInst, lpProcName)); lpfn)
					{
						if (lpMsgHandle = SetWindowsHookEx(WH_GETMESSAGE, lpfn, hInst, dwThreadId); lpMsgHandle)
						{
							return FreeLibrary(hInst) == TRUE;
						}
					}
				}
			}
			return false;
		}

		bool Message::UninstallWindowsMessageEx()
		{
			if (lpMsgHandle)
			{
				auto MsgHook = lpMsgHandle;
				lpMsgHandle = nullptr;
				return UnhookWindowsHookEx(MsgHook);
			}
			return false;
		}

		DWORD Message::GetProcessId()
		{
			return lpdwProcessId;
		}

		DWORD Message::GetThreadId()
		{
			return dwThreadId;
		}
	};
};