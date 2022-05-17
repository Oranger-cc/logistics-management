#include "Account.h"
#include <iostream>
#include <fstream>

Account::Account()
{
	static std::string op,userName;
	p = nullptr;
	while (1)
	{
		std::cout << "Please choose a way to continue:\nl:login\nr:register\n" << std::endl;
		std::cin >> op;
		if (op[0] == 'l')
		{
			std::cout << "Please input your username: ";
			std::cout.flush();
			std::cin >> userName;
			if (login(userName)==LOGIN_SUCCESS)
				break;
		}
		else if (op[0] == 'r')
		{
			std::cout << "Please input your username: ";
			std::cout.flush();
			std::cin >> userName;
			//
		}
		else
		{
			std::cout << "Invalid input, try again." << std::endl;
		}
	}
	// listen
}

Account::~Account()
{
	delete p;
	p = nullptr;
}

int Account::regist(std::string userName)
{
	static char buf[30] = { 0 };
	if(userName.length()>20)
		
	return 0;
}

int Account::login(std::string userName)
{
	static char buf[30] = {0};
	static std::string passwd, input, userFileName;
	static int res;
	if (userName.length() > 20)
		return LOGIN_FAIL;
	sprintf_s(buf, "key/%s.txt", userName.c_str());
	std::ifstream fin(buf);
	if (!fin)
	{
		std::cerr << "The user does not exist.\n\n";
		return LOGIN_FAIL;
	}
	std::cout << "Please input password: ";
	std::cout.flush();
	std::cin >> input;
	fin >> passwd;
	res = passwd.compare(input);
	if (res == LOGIN_SUCCESS)
	{
		std::cerr << "Welcome, " << userName << "!\n";
		fin >> userFileName;
		switch (userFileName[5]) // certain length ?
		{
		case 'U':
			p = new User(userFileName);
			break;
		default:
			std::cerr << "Invalid user type.\n";
			break;
		}
	}
	else
	{
		std::cerr << "Wrong password!\n";
	}
	return res;
}
