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
#define getCope(x, a, b)							(x >= a && x <= b) 
#define getBits(x)									(getCope(x, '0', '9') ? (x - '0') : ((x & (~0x20)) - 'A' + 0xa))
#define getByte(x)									(getBits(x[0]) << 4 | getBits(x[1]))
#define CryVirtualQueryMemory(_Type, x)				*(_Type *)(x)

#define MetaType(_Type) qRegisterMetaType<_Type>(#_Type);

/* End */
#endif