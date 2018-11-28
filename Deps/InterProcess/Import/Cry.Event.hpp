#pragma once
#include <Winsock2.h>
namespace Cry
{
	namespace Import
	{
		class InitializeEvent
		{
		public:
			InitializeEvent()
			{
				WSADATA WSAData;
				WSAStartup(MAKEWORD(2, 2), &WSAData);
			}
			~InitializeEvent()
			{
				WSACleanup();
			}
		};
	}
}