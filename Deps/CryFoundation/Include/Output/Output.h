#if !defined(CRY_OUTPUT_H)
#define CRY_OUTPUT_H
#pragma once
#include <Foundation.h>
#include <Kernel.h>
namespace Cry
{
	namespace Kernel
	{
		class FunctionExport Output
		{
		public:
			static void CryOutputDebugString(_In_opt_ LPCTSTR lpszString, DWORD dwMilliseconds = 100, bool OpenConsole = false);
		protected:
			Output(const Output&) = delete;
			Output & operator = (const Output&) = delete;
		};
	}
}
#endif