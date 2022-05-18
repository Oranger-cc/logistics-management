#include "Account.h"
#include <iostream>
#include <fstream>

Account::Account()
{
	std::string op,userName;
	
	// initial system
	std::ifstream fin("info.txt");
	fin >> numberUser >> numberPackage;
	fin.close();
	p = nullptr;

	// login an account
	while (1)
	{
		std::cout << "==============================\n"
			<< "Please choose a way to continue:\n"
			<< "l: login\n"
			<< "r: register\n"
			<< "q: quit\n" << std::endl;
		std::cin >> op;
		if (op[0] == 'l')
		{
			std::cout << "Please input your username: " << std::endl;
			std::cin >> userName;
			if (login(userName)==LOGIN_SUCCESS)
				break;
		}
		else if (op[0] == 'r')
		{
			regist();
		}
		else if (op[0] == 'q')
		{
			return;
		}
		else
		{
			std::cout << "Invalid input, try again." << std::endl;
		}
	}

	// listen
	p->listen(numberUser,numberPackage);
}

Account::~Account()
{
	delete p;
	p = nullptr;

	std::ofstream fout("info.txt");
	fout << numberUser << std::endl << numberPackage << std::endl;
	fout.close();

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
	if (!fin.is_open())
	{
		std::cerr << "The user does not exist.\n" << std::endl;
		fin.close();
		return LOGIN_FAIL;
	}
	std::cout << "Please input password: " << std::endl;
	std::cin >> input;
	fin >> passwd;
	res = passwd.compare(input);
	if (res == LOGIN_SUCCESS)
	{
		std::cerr << "Welcome, " << userName << "!\n" << std::endl;
		fin >> userFileName;
		switch (userFileName[5]) // certain length ?
		{
		case 'U':
			p = new User(userFileName);
			break;
		default:
			std::cerr << "Invalid user type.\n" << std::endl;
			break;
		}
	}
	else
	{
		std::cerr << "Wrong password!\n" << std::endl;
	}
	fin.close();
	return res;
}

int Account::regist()
{
	static char buf[30] = { 0 };
	static std:: string userName;
	std::cout << "Please input your username (no more than 20 chars):" << std::endl;
	std::cin >> userName;
	if (userName.length() > 20)
		return REGISTER_FAIL;
	sprintf_s(buf, "key/%s.txt", userName.c_str());
	std::ifstream fin(buf);
	if (fin.is_open())
	{
		fin.close();
		std::cerr << "The username has been registered.\n" << std::endl;
		return REGISTER_FAIL;
	}
	fin.close();

	// begin to create user, not able to cancel
	sprintf_s(buf, "data/User%d.txt", ++numberUser);
	p = new User(numberUser,userName,buf);
	return REGISTER_SUCCESS;
}
