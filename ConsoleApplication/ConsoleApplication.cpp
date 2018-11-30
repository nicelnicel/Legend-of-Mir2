// ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <StringXor.h>
void PutsMasks(std::string lpszString)
{
	if (lpszString.empty())
	{
		return;
	}
	std::cout << "加密文本：" << lpszString << std::endl;
	std::string XorDes = Cry::Text::Xor::Operate(lpszString);
	std::cout << "加密结果" << std::endl;
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
	char lpszText[MAX_PATH];
	while (gets_s(lpszText))
	{
		system("cls");
		PutsMasks(lpszText);
	}
	std::cout << "exit" << std::endl;
	system("pause");
	return 0;
}
