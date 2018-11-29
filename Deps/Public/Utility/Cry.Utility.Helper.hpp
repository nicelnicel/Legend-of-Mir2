#if !defined(_HELPER_HEAD_)
/* Star */
#define _HELPER_HEAD_
#pragma once
#include <tchar.h>
#include <debugapi.h>
// 公共帮助
#if !defined(_DEBUG)
	# define DebugMsg(...) do { TCHAR debugMsg[MAX_PATH]; _sntprintf_s(debugMsg, _countof(debugMsg), _TRUNCATE, ##__VA_ARGS__); OutputDebugString(debugMsg); } while(0)
#else
	# define DebugMsg(...) do { TCHAR debugMsg[MAX_PATH]; _sntprintf_s(debugMsg, _countof(debugMsg), _TRUNCATE, ##__VA_ARGS__); OutputDebugString(debugMsg); } while(0)
#endif
// 读写内存
#define getCope(_x, a, b)							(_x >= a && _x <= b) 
#define getBits(_x)									(getCope(_x, '0', '9') ? (_x - '0') : ((_x & (~0x20)) - 'A' + 0xa))
#define getByte(_x)									(getBits(_x[0]) << 4 | getBits(_x[1]))
#define CryVirtualQueryMemory(_Type, _x)			*(_Type *)(_x)

#define MetaType(_Type) qRegisterMetaType<_Type>(#_Type);

/* End */
#endif