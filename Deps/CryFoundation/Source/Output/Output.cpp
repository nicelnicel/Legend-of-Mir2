#include <Output/Output.h>
namespace Cry
{
	namespace Kernel
	{
		void Output::CryOutputDebugString(LPCTSTR lpszString, DWORD dwMilliseconds, bool OpenConsole)
		{
			if (HANDLE hAckEvent = OpenEvent(SYNCHRONIZE, FALSE, TEXT("CRY_BUFFER_READY")))
			{
				if (HANDLE hReadyEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("CRY_DATA_READY")))
				{
					if (WaitForSingleObject(hAckEvent, dwMilliseconds) == WAIT_OBJECT_0)
					{
						if (OpenConsole && GetConsoleWindow())
						{
							_tprintf(lpszString);
						}
						if (HANDLE hMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, TEXT("CRY_BUFFER")))
						{
							if (LPDBWINBUFFER lpBuffer = (LPDBWINBUFFER)(MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0)))
							{
								CopyMemory(lpBuffer->szString, lpszString, lstrlen(lpszString));
								SetEvent(hReadyEvent);
								UnmapViewOfFile(lpBuffer); 
							}
							CloseHandle(hMapping);
						}
					}
					CloseHandle(hReadyEvent);
					CloseHandle(hAckEvent);
				}
			}
		}
	}
}