#include <Module.h>
#include <phbase.h>
namespace Cry
{
	namespace Kernel
	{
		namespace Value
		{ 
			char lpFiledir[MAX_PATH]; 
		};
		PTEB Module::GetContextTeb()
		{
			PTEB Teb;
			__asm
			{
				mov     eax, dword ptr fs : [0x18]
				mov     Teb, eax
			}
			return Teb;
		}

		bool Module::HideModuleByHandle(HMODULE hInstance)
		{
			PPEB Peb = GetContextTeb()->ProcessEnvironmentBlock;
			PLDR_DATA_TABLE_ENTRY Blink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(&Peb->Ldr->InLoadOrderModuleList);
			PLDR_DATA_TABLE_ENTRY Flink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(Peb->Ldr->InLoadOrderModuleList.Flink);
			while (Flink != Blink)
			{
				if (PLDR_DATA_TABLE_ENTRY(Flink)->DllBase == hInstance)
				{
					// ¶ÏÁ´
					Flink->InLoadOrderLinks.Flink->Blink = Flink->InLoadOrderLinks.Blink;
					Flink->InLoadOrderLinks.Blink->Flink = Flink->InLoadOrderLinks.Flink;
					Flink->InMemoryOrderLinks.Flink->Blink = Flink->InMemoryOrderLinks.Blink;
					Flink->InMemoryOrderLinks.Blink->Flink = Flink->InMemoryOrderLinks.Flink;
					Flink->InInitializationOrderLinks.Flink->Blink = Flink->InInitializationOrderLinks.Blink;
					Flink->InInitializationOrderLinks.Blink->Flink = Flink->InInitializationOrderLinks.Flink;
					return true;
				}
				Flink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(Flink)->InLoadOrderLinks.Flink);
			}
			return false;
		}
		bool Module::HideModuleByHandleEx(HMODULE hInstance, HANDLE hHandle)
		{
			PROCESS_BASIC_INFORMATION pbi;
			if (!NT_SUCCESS(NtQueryInformationProcess(hHandle, ProcessBasicInformation, &pbi, sizeof(pbi), NULL)))
			{
				return false;
			}
			DWORD pflOldProtect = 0;
			if (!VirtualProtect(hInstance, 1024, PAGE_EXECUTE_READWRITE, &pflOldProtect))
			{
				return false;
			}
			ZeroMemory(hInstance, 1024);
			VirtualProtect(hInstance, 1024, pflOldProtect, 0);
			PPEB Peb = pbi.PebBaseAddress;
			PLDR_DATA_TABLE_ENTRY Blink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(&Peb->Ldr->InLoadOrderModuleList);
			PLDR_DATA_TABLE_ENTRY Flink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(Peb->Ldr->InLoadOrderModuleList.Flink);
			while (Flink != Blink)
			{
				if (PLDR_DATA_TABLE_ENTRY(Flink)->DllBase == hInstance)
				{
					ZeroMemory(PLDR_DATA_TABLE_ENTRY(Flink)->FullDllName.Buffer, PLDR_DATA_TABLE_ENTRY(Flink)->FullDllName.Length);
					ZeroMemory(PLDR_DATA_TABLE_ENTRY(Flink)->BaseDllName.Buffer, PLDR_DATA_TABLE_ENTRY(Flink)->BaseDllName.Length);
					// ¶ÏÁ´
					Flink->InLoadOrderLinks.Flink->Blink = Flink->InLoadOrderLinks.Blink;
					Flink->InLoadOrderLinks.Blink->Flink = Flink->InLoadOrderLinks.Flink;
					Flink->InMemoryOrderLinks.Flink->Blink = Flink->InMemoryOrderLinks.Blink;
					Flink->InMemoryOrderLinks.Blink->Flink = Flink->InMemoryOrderLinks.Flink;
					Flink->InInitializationOrderLinks.Flink->Blink = Flink->InInitializationOrderLinks.Blink;
					Flink->InInitializationOrderLinks.Blink->Flink = Flink->InInitializationOrderLinks.Flink;
					return true;
				}
				Flink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(Flink)->InLoadOrderLinks.Flink);
			}
			return false;
		}
		bool Module::HideBreakpoint(HANDLE hThread)
		{
			return NT_SUCCESS(NtSetInformationThread(hThread, ThreadHideFromDebugger, 0, 0));
		}
		bool Module::EnumeModuleInfo(HANDLE hHandle)
		{
			PROCESS_BASIC_INFORMATION pbi;
			if (!NT_SUCCESS(NtQueryInformationProcess(hHandle, ProcessBasicInformation, &pbi, sizeof(pbi), NULL)))
			{
				return false;
			}
			PPEB Peb = pbi.PebBaseAddress;
			PLDR_DATA_TABLE_ENTRY Blink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(&Peb->Ldr->InLoadOrderModuleList);
			PLDR_DATA_TABLE_ENTRY Flink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(Peb->Ldr->InLoadOrderModuleList.Flink);
			while (Flink != Blink)
			{
				wprintf(L"%s\r\n", PLDR_DATA_TABLE_ENTRY(Flink)->FullDllName.Buffer);
				Flink = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(Flink)->InLoadOrderLinks.Flink);
			}
			return true;
		}
		bool Module::GetModuleFullPath(HMODULE hInstance, char* lpFilename)
		{
			uint32_t dwCount = GetModuleFileName(hInstance, lpFilename, MAX_PATH);
			*_tcsrchr(reinterpret_cast<char*>(CopyMemory(Value::lpFiledir, lpFilename, dwCount)), TEXT('\\')) = 0; _tcscat(Value::lpFiledir, TEXT("\\Cache"));
			return ((dwCount > 0) && (dwCount <= MAX_PATH));
		}
	}
}