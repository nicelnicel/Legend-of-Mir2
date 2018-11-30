#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <utility>
#include <functional>
class MyClass
{
public:
	MyClass() { i = 0; }
	~MyClass() {}
public:
	void  Test1()
	{
		++i;
		this->Test3();
	}
	void WINAPI Test2();
	void WINAPI Test3();
	LRESULT myhook(int a, WPARAM b, LPARAM c)
	{
		printf("%d %d %d\n", a, b, c);
		return 0;
	}
	void Init()
	{
		

	}
private:
	uint32_t i;
};
void WINAPI MyClass::Test2()
{
	++i;
	this->Test1();
	return;
}
template<class Fun, class... Args>
constexpr auto wrap_call(Fun&& f, Args&&... args)
noexcept(std::forward<Fun>(f)(std::forward<Args>(args)...)) -> decltype(std::forward<Fun>(f)(std::forward<Args>(args)...))
{
	return std::forward<Fun>(f)(std::forward<Args>(args)...);
}
std::function<LRESULT __cdecl(int, WPARAM, LPARAM)> func;
void __declspec(naked) MyClass::Test3()
{
	func = std::bind(&MyClass::myhook, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	
	
	func(1, 2, 3);
	__asm
	{
		ret 0x4
	}
}
int asdasd(int a1, int a2, int a3)
{
	return 1;
}

int main()
{
	MyClass Class;
	
	printf("Test1:%p\n", std::bind(&MyClass::Test1));
	printf("Test2:%p\n", std::bind(&MyClass::Test2));
	printf("Test3:%p\n", std::bind(&MyClass::Test3));

	printf("Test4:%p\n", decltype(&MyClass::Test3)());
	;
	Class.Test3();
	getchar();
	return 0;
}