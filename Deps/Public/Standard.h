#if !defined(_STD_HEAD_)
#define _STD_HEAD_
#pragma once
// 从 Windows 头文件中排除极少使用的内容
#if !defined(WIN32_LEAN_AND_MEAN)
	#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning( disable: 4005 ) // warning C4005 : 'va_copy' : macro redefinition
#pragma warning( disable: 4251 )
#pragma warning( disable: 4996 ) // warning C4996: 'strerror': This function or variable may be unsafe. Consider using strerror_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#pragma warning( disable: 4244 4251 4355 4715 4800 4996 4005 4819)
#pragma warning( disable: 4530 ) // C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include\xlocale(341): warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
#pragma warning( disable: 4577 ) // C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include\exception(359): warning C4577: 'noexcept' used with no exception handling mode specified; termination on exception is not guaranteed. Specify /EHsc
#pragma warning( disable: 4503 ) // c:\program files (x86)\microsoft visual studio 14.0\vc\include\functional(357): warning C4503: '__LINE__Var': decorated name length exceeded, name was truncated
#pragma warning( disable: 4477 ) // warning C4477: “_snprintf_s”: 格式字符串“%?”需要类型“xxx”的参数，但可变参数 1 拥有了类型“xxx”

#include <SDKDDKVer.h>
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ 运行时头文件
#include <iostream>
// 公共库
#if !defined(_DEBUG)
	#define DebugMsg(...) do { TCHAR debugMsg[MAX_PATH]; _sntprintf_s(debugMsg, _countof(debugMsg), _TRUNCATE, ##__VA_ARGS__); OutputDebugString(debugMsg); } while(0)
#else
	#define DebugMsg(...) do { TCHAR debugMsg[MAX_PATH]; _sntprintf_s(debugMsg, _countof(debugMsg), _TRUNCATE, ##__VA_ARGS__); OutputDebugString(debugMsg); } while(0)
#endif

namespace Cry
{
	namespace Kernel
	{
		namespace Value { extern char lpFiledir[MAX_PATH]; };
	};
};
// 在此处引用程序需要的其他标头
// Boost 排除依赖项
#if !defined(BOOST_DATE_TIME_NO_LIB)
	#define BOOST_DATE_TIME_NO_LIB
	//#define BOOST_INTERPROCESS_SHARED_DIR_PATH TEXT(Cry::Kernel::Value::lpFiledir)
#endif

// 消息队列名字
#if !defined(MESSAGE_UNIQUE_NAME)
	#define Buffer_Name TEXT("Interprocess.Message.Queue")
	#define Buffer_Size 1024
#endif
#define HeadSize (sizeof(uint32_t) + sizeof(uint32_t))
#define TYPETEXT(x) TEXT(#x)

// 读写内存
#define CryWrite(t, x) *(t*)(x)
#define CryRead(t, x)  *(t*)(x)
#if !defined(_USRDLL)
#ifdef _M_IX86
# pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif _M_IA64
# pragmacomment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif _M_X64
# pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
# pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
#endif

