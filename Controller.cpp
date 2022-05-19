#include "Controller.h"
#include <fstream>

Controller::Controller()
{
	std::ifstream fin;
	char buf[30];

	fin.open("data/info.txt");
	fin >> numberUser >> numberPackage;
	fin.clear();
	fin.close();

	user = new User[MAX_USER];
	for (int i = 1; i <= numberUser; i++)
	{
		sprintf_s(buf, "data/User%d.txt", i);
		user[i].init(buf);
	}

	admin = new Admin("data/Admin1.txt");
	admin->init();

	package = new Package[MAX_PACKAGE];
	for (int i = 1; i <= numberPackage; i++)
	{
		sprintf_s(buf, "data/Package%d.txt", i);
		package[i].init(buf);
	}

	p = nullptr;

	ft=new Filter;
}

Controller::~Controller()
{
	saveInfo();

	for (int i = 1; i <= numberUser; i++)
		user[i].save();
	delete[] user;
	user = nullptr;
	
	admin->save();
	delete admin;

	for (int i = 1; i <= numberPackage; i++)
		package[i].save();
	delete[] package;
	package = nullptr;

	delete ft;
}

int Controller::saveInfo()
{
	std::ofstream fout("data/info.txt");
	fout << numberUser << ' ' << numberPackage;
	fout.clear();
	fout.close();
	return 0;
}

int Controller::login(std::string userName)
{
	static char buf[30] = { 0 };
	static std::string passwd, input, userFileName;
	static int res, userId;
	if (userName.length() > 20)
	{
		std::cout << "The user does not exist.\n" << std::endl;
		p = nullptr;
		return 1;
	}
	sprintf_s(buf, "key/%s.txt", userName.c_str());
	std::ifstream fin(buf);
	if (!fin.is_open())
	{
		std::cout << "The user does not exist.\n" << std::endl;
		fin.close();
		p = nullptr;
		return 1;
	}
	std::cout << "Please input password: " << std::endl;
	std::cin >> input;
	fin >> passwd;
	res = passwd.compare(input);
	if (res == 0)
	{
		std::cout << "Welcome, " << userName << "!\n" << std::endl;
		fin >> userFileName >> userId;
		switch (userFileName[0]) // User/Admin id
		{
		case 'U':
			p = &user[userId];
			break;
		case 'A':
			p = admin;
			break;
		default:
			std::cout << "Invalid user type.\n" << std::endl;
			break;
		}
	}
	else
	{
		std::cout << "Wrong password!\n" << std::endl;
	}
	fin.close();
	return res;
}

int Controller::regist()
{
	static char buf[30] = { 0 };
	static std::string userName,tmp1,tmp2,tmpPasswd;
	std::cout << "Please input your username (no more than 20 chars):" << std::endl;
	std::cin >> userName;
	if (userName.length() > 20)
	{
		std::cout << "The username is too long. Failed.\n" << std::endl;
		return 1;
	}
	sprintf_s(buf, "key/%s.txt", userName.c_str());
	std::ifstream fin(buf);
	if (fin.is_open())
	{
		fin.close();
		std::cout << "The username has been registered. Failed.\n" << std::endl;
		return 1;
	}
	fin.close();

	// begin to create user
	while (1)
	{
		std::cout << "Please input your password:" << std::endl;
		std::cin >> tmp1;
		std::cout << "Please input your password again to ensure:" << std::endl;
		std::cin >> tmp2;
		if (tmp1.compare(tmp2) == 0)
			break;
		else
			std::cout << "The password do not match. Try again." << std::endl;
	}
	tmpPasswd = tmp1;
	std::cout << "Please input your telephone number:" << std::endl;
	std::cin >> tmp1;
	std::cout << "Please input your location:" << std::endl;
	std::cin >> tmp2;

	numberUser++;
	sprintf_s(buf, "data/User%d.txt", numberUser);
	user[numberUser] = User(numberUser, userName, buf, tmpPasswd, tmp1, tmp2);
	
	saveInfo();
	user[numberUser].save();
	std::cout << "Register successfully!" << std::endl;

	return 0;
}

int Controller::sendNewPackage(int from, int to)
{
	++numberPackage;
	package[numberPackage] = Package(numberPackage, PACKAGE_READY, from, to);
	package[numberPackage].send(from);
	user[from].recharge(-15);
	admin->recharge(15);
	user[from].appendSend(numberPackage);
	user[to].appendRecv(numberPackage);
	return 0;
}

int Controller::recvPackage(int packageId, int to)
{
	if (1 <= packageId && packageId <= numberPackage)
	{
		return package[packageId].recv(to);
	}
	return 1;
}
