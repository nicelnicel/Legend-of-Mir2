// ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <iostream>
#if !defined(BOOST_DATE_TIME_NO_LIB)
#define BOOST_DATE_TIME_NO_LIB
#endif
#include <boost/interprocess/ipc/message_queue.hpp>
struct message_test
{
	uint32_t u1;
	uint32_t u2;
	uint32_t u3;
	uint32_t u4;
	int8_t   szText[MAX_PATH];
};
int main()
{
	message_test _Test{ 1,2,3,4, "1234" };
	printf("%d\n", sizeof(_Test));
	getchar();
	return 0;
	try
	{
		boost::interprocess::message_queue mq(boost::interprocess::open_only, "message_queue");

		for (uint32_t i = 0; i < 100; ++i)
		{
			TCHAR lpszText[MAX_PATH] = { 0 };
			unsigned int priority;
			boost::interprocess::message_queue::size_type recvd_size;
			mq.receive(lpszText, MAX_PATH, recvd_size, priority);
			printf("%s\n", lpszText);
		}
	}
	catch (boost::interprocess::interprocess_exception &ex)
	{
		printf("%d\n", ex.get_error_code());
	}
	


	getchar();
	return 0;

	HHOOK m_Hook = NULL;
	HWND GamehWnd = 0;
	for (;;)
	{
		GamehWnd = ::FindWindow("TApplication", "Legend of Mir2");
		Sleep(50);
		if (GamehWnd)
		{
			break;
		}
	}
	printf("呼出\n");
	if (GamehWnd)
	{
		DWORD fProcessId = 0;

		DWORD fThreadProcessId = GetWindowThreadProcessId(GamehWnd, &fProcessId);

		HINSTANCE hInst = LoadLibraryEx("./Library.dll", NULL, DONT_RESOLVE_DLL_REFERENCES);
		if (hInst)
		{
			HOOKPROC lpfn = (HOOKPROC)GetProcAddress(hInst, "InterFaceDll");
			if (lpfn)
			{
				m_Hook = SetWindowsHookEx(WH_GETMESSAGE, lpfn, hInst, fThreadProcessId);
				if (m_Hook)
				{
					printf("HOOK成功\n");
				}
				else
				{
					printf("HOOK失败\n");
				}
				FreeLibrary(hInst);
			}
			else
			{
				printf("获得子程序失败\n");
			}
		}
		else
		{
			printf("加载DLL失败 错误代码：%d\n", GetLastError());
		}
		if (!PostMessage(GamehWnd, WM_USER + 9527, NULL, NULL))
		{
			printf("发送卸载消息失败\n");
			getchar();
		}
		getchar();
		printf("卸载消息\n");
		if (!UnhookWindowsHookEx(m_Hook))
		{
			printf("卸载HOOK失败\n");
			getchar();
		}
		getchar();
	}
    std::cout << "Hello World!\n"; 
}
