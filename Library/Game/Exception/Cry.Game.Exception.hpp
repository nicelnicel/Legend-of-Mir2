#if !defined(_Exception_)
/* Star */
#define _Exception_
#pragma once
#include <string>
#include <Global>
namespace Cry
{
	namespace Game
	{
		/// 打造简单的异常处理类慢慢完善
		class Exception
		{
		public:
			Exception(const std::string & lpszString) : m_lpszString(lpszString)
			{

			};
			~Exception()
			{
				m_lpszString.clear();
			};
		public:
			static u32 ExceptionHandler(u32 dwExceptionCode)
			{
				u32 ExceptionCode = EXCEPTION_CONTINUE_SEARCH;
				switch (dwExceptionCode)
				{
				case EXCEPTION_ACCESS_VIOLATION:				DebugMsg("读写内存异常，错误代码：%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_DATATYPE_MISALIGNMENT:			DebugMsg("数据类型未对齐异常，错误代码：%x\n", dwExceptionCode); break;
				case EXCEPTION_BREAKPOINT:						DebugMsg("中断异常，错误代码：%x\n", dwExceptionCode); break;
				case EXCEPTION_SINGLE_STEP:						DebugMsg("单步中断异常，错误代码：%x\n", dwExceptionCode); break;
				case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:			DebugMsg("数组越界异常，错误代码：%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_FLT_DENORMAL_OPERAND:
				case EXCEPTION_FLT_DIVIDE_BY_ZERO:
				case EXCEPTION_FLT_INEXACT_RESULT:
				case EXCEPTION_FLT_INVALID_OPERATION:
				case EXCEPTION_FLT_OVERFLOW:
				case EXCEPTION_FLT_STACK_CHECK:
				case EXCEPTION_FLT_UNDERFLOW:					DebugMsg("浮点数计算异常，错误代码：%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_INT_DIVIDE_BY_ZERO:				DebugMsg("被0除异常，错误代码：%x\n", dwExceptionCode);					ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_INT_OVERFLOW:					DebugMsg("数据溢出异常，错误代码：%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_IN_PAGE_ERROR:					DebugMsg("页错误异常，错误代码：%x\n", dwExceptionCode);					ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_ILLEGAL_INSTRUCTION:				DebugMsg("非法指令异常，错误代码：%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				case EXCEPTION_STACK_OVERFLOW:					DebugMsg("堆栈溢出异常，错误代码：%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_EXECUTE_HANDLER;			break;
				case EXCEPTION_INVALID_HANDLE:					DebugMsg("无效句病异常，错误代码：%x\n", dwExceptionCode);				ExceptionCode = EXCEPTION_CONTINUE_EXECUTION;		break;
				default:
				{
					if (dwExceptionCode & (1 << 29))
						DebugMsg("自定义的软件异常，错误代码：%x\n", dwExceptionCode);
					else
						DebugMsg("其它异常，错误代码：%x\n", dwExceptionCode);
					break;
				}
				}
				// 
				return ExceptionCode;
			}
			std::string & Info() { return m_lpszString; };
		private:
			std::string				m_lpszString;
		};
	};
};
#endif