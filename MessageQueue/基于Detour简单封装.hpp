#include <Windows.h>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <Detours.h>
/// 以下注释为作者早年写的，现在弃之。
/*
#define DEF_DETOUR_FUNC( func , returntype , proto ) \
	returntype WINAPI func##_Detour proto; \
	typedef returntype ( WINAPI * func##_t ) proto; \
	func##_t p##func = nullptr;

#define HookFunc( module, funcname, func)\
	DetourTransactionBegin(); \
	DetourUpdateThread(GetCurrentThread()); \
	p##func = (func##_t)DetourFindFunction(module, funcname); \
	DetourAttach(&(PVOID&)p##func, func##_Detour, 0); \
	DetourTransactionCommit();

#define UninstallHookFunc(func, mode) \
	DetourTransactionBegin(); \
	DetourUpdateThread(GetCurrentThread()); \
	DetourDetach(&(PVOID&)p##func, func##_Detour, mode); \
	DetourTransactionCommit(mode);

#define HookGameFunc( addr, func, mode)\
	DetourTransactionBegin(); \
	DetourUpdateThread(GetCurrentThread()); \
	p##func = (func##_t)addr; \
	DetourAttach(&(PVOID&)p##func, func##_Detour, mode); \
	if(DetourTransactionCommit(mode) != NO_ERROR) \
	{ \
		Success &= false; \
	}


#define UninstallGameHookFunc(func, mode) \
	DetourTransactionBegin(); \
	DetourUpdateThread(GetCurrentThread()); \
	DetourDetach(&(PVOID&)p##func, func##_Detour, mode); \
	if(DetourTransactionCommit(mode) != NO_ERROR) \
	{ \
		Success &= false; \
	}
*/
class HookClass
{
public:
	void  MyMessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
	{
		printf("MyMessageBox\n");
	}
	void WINAPI MyMessageBox_Detour(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
	{
		printf("Hook MyMessageBox\n");
	}
	void MyMessageBoxDeclspec();
};
void __declspec(naked) HookClass::MyMessageBoxDeclspec()
{
	this->MyMessageBox_Detour(0, "1", "2", 3);
	__asm
	{
		ret 0x4
	}
}
class DetourEngine
{
public:
	DetourEngine() = default;
	~DetourEngine()
	{
		m_DataBase.clear();
	}
public:
	using lPointer = void *;
	struct tag
	{
		/// _Ty1
		lPointer ppPointer;
		/// _Ty2
		lPointer pDetour;
	};
public:
	/// 参数1：强制左值[否]
	/// 参数2：强制左值[是]
	/// 参数3：变参备用 -> 理论上讲填不填都一样 bind 只是取地址
	/// 说 明：代码为预览版本、如发现Bug请自行修复，剩下请自行完善吧。
	template<typename _Ty1, typename _Ty2, class... _Types>
	constexpr auto InstallHookFunc(const std::string & lpszDefined, _Ty1 && ppPointer, _Ty2 && pDetour, _Types &&... _Args)
	{
		auto bSucess = true;
		bSucess &= !DetourTransactionBegin();
		bSucess &= !DetourUpdateThread(GetCurrentThread());
		bSucess &= !DetourAttach(std::move((&(lPointer&)(ppPointer))), std::move(*&(lPointer&)(std::bind(std::forward<_Ty2>(pDetour), std::forward<_Types>(_Args)...))));
		bSucess &= !DetourTransactionCommit();
		if (bSucess)
		{
			m_DataBase.emplace(std::make_pair(lpszDefined, tag{ std::move((*&(lPointer&)ppPointer)), std::move(*&(lPointer&)(std::bind(std::forward<_Ty2>(pDetour), std::forward<_Types>(_Args)...))) }));
		}
		return bSucess;
	}
	bool UninstallAllHookFunc()
	{
		auto bSucess = true;
		if (m_DataBase.empty())
		{
			return false;
		}
		for (auto & [m_lpszDefined, m_Tag] : m_DataBase)
		{
			if (m_Tag.ppPointer && m_Tag.pDetour)
			{
				bSucess &= !DetourTransactionBegin();
				bSucess &= !DetourUpdateThread(GetCurrentThread());
				bSucess &= !DetourAttach(std::move((&(PVOID&)(m_Tag.pDetour))), std::move(m_Tag.ppPointer));
				bSucess &= !DetourTransactionCommit();
			}
			else
			{
				/// 卸载 m_lpszDefined 失败
				bSucess &= false;
				break;
			}
		}
		return bSucess;
	}
	bool UninstallHookFunc(const std::string & lpszDefined)
	{
		auto bSucess = true;
		if (m_DataBase.empty())
		{
			return false;
		}
		for (auto & [m_lpszDefined, m_Tag] : m_DataBase)
		{
			if (m_lpszDefined == lpszDefined && m_Tag.ppPointer && m_Tag.pDetour)
			{
				bSucess &= !DetourTransactionBegin();
				bSucess &= !DetourUpdateThread(GetCurrentThread());
				bSucess &= !DetourAttach(std::move((&(PVOID&)(m_Tag.pDetour))), std::move(m_Tag.ppPointer));
				bSucess &= !DetourTransactionCommit();
			}
			else
			{
				/// 卸载 m_lpszDefined 失败
				bSucess &= false;
				break;
			}
		}
		return bSucess;
	}
private:
	std::unordered_map<std::string, tag>											m_DataBase;
};
int main()
{
	HookClass A;
	auto FuncA = std::bind(&HookClass::MyMessageBox, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	auto FuncB = std::bind(&HookClass::MyMessageBoxDeclspec);
	//std::function<void(int)>;
	DetourEngine Hook;
	Hook.InstallHookFunc("123", FuncA, FuncB);
	A.MyMessageBox(0, "123", "456", 2);
	Hook.UninstallHookFunc("123");
	A.MyMessageBox(0, "123", "456", 2);
	getchar();
	return 0;
}