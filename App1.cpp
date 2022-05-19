// App1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// Logistics Management System

#include <iostream>
#include <string>
#include "Controller.h"

Controller* now;

int main()
{
	std::string op, userName;
    now = new Controller;

	while (1)
	{
		std::cout << "==============================\n"
			<< "Please choose a way to continue:\n"
			<< "l: login\n"
			<< "r: register\n"
			<< "q: quit\n" 
			<< "==============================\n" << std::endl;
		std::cin >> op;
		if (op[0] == 'l')
		{
			std::cout << "Please input your username: " << std::endl;
			std::cin >> userName;
			if (now->login(userName) == 0)
				break;
		}
		else if (op[0] == 'r')
		{
			now->regist();
		}
		else if (op[0] == 'q')
		{
			return 0;
		}
		else
		{
			std::cout << "Invalid input, try again." << std::endl;
		}
	}
	
	now->p->listen();

	delete now;
    return 0;
}

