// ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <iostream>
#include <StringXor.h>

void PutsMasks()
{
	std::string XorDes = Cry::Text::Xor::Operate("发送文本");
	printf("加密结果\n");
	for (uint32_t i = 0; i < XorDes.size(); ++i)
	{
		printf("0x%02X, ", (uint8_t)XorDes[i]);
	}
	printf("0x00, 0x00\n");

	for (uint32_t i = 0; i < XorDes.size(); ++i)
	{
		printf("\\x%02X", (uint8_t)XorDes[i]);
	}
	printf("\\x00\\x00\n");

	
}

int main()
{
	PutsMasks();
	printf("解密结果：%s\n", Cry::Text::Xor::Operate(Cry::Text::Xor::Operate("我爱中国").c_str()).c_str());
	getchar();
    std::cout << "Hello World!\n"; 
	return 0;
}
