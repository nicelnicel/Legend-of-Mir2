#if !defined(CRY_KERNEL_H)
#define CRY_KERNEL_H
#pragma once
#include <Windows.h>
#include <stdint.h>
#define MAX_DEBUG_BUF_LEN (4096)
#pragma pack(push)
#pragma pack(1)
typedef struct DBWINBUFFER
{
	uint32_t		uId;
	char			szString[MAX_DEBUG_BUF_LEN - sizeof(uint32_t)];
} DBWINBUFFER, *LPDBWINBUFFER;
#pragma pack(pop)
#endif