#include "Controller.h"
#include <fstream>

Controller::Controller()
{
	std::ifstream fin;
	char buf[30];

	fin.open("data/info.txt");
	fin >> numberUser >> numberPackage >> numberCourier;
	fin.clear();
	fin.close();

	user = new User[MAX_USER];
	for (int i = 1; i <= numberUser; i++)
	{
		sprintf_s(buf, "data/User%d.txt", i);
		user[i].init(buf);
	}

	courier = new Courier[MAX_COURIER];
	for (int i = 1; i <= numberCourier; i++)
	{
		sprintf_s(buf, "data/Courier%d.txt", i);
		courier[i].init(buf);
	}

	admin = new Admin("data/Admin0.txt");
	admin->init();

	for (int i = 1; i <= numberPackage; i++)
	{
		sprintf_s(buf, "data/Package%d.txt", i);
		int _type;
		std::ifstream fin(buf);
		if (fin.is_open())
		{
			fin >> _type;
			fin.close();
			switch (_type)
			{
			case FRAGILE:
				package[i] = new Fragile(buf);
				break;
			case BOOK:
				package[i] = new Book(buf);
				break;
			case NORMALPACKAGE:
				package[i] = new Normalpack(buf);
				break;
			}
		}
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
	
	for (int i = 1; i <= numberCourier; i++)
		courier[i].save();
	delete[] courier;
	courier = nullptr;

	admin->save();
	delete admin;

	for (int i = 1; i <= numberPackage; i++)
	{
		package[i]->save();
		delete package[i];
		package[i] = nullptr;
	}

	delete ft;
}

int Controller::saveInfo()
{
	std::ofstream fout("data/info.txt");
	fout << numberUser << ' ' << numberPackage << ' ' << numberCourier;
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
		case 'C':
			p = &courier[userId];
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
		std::cout << "The username is too long, failed.\n" << std::endl;
		return 1;
	}
	sprintf_s(buf, "key/%s.txt", userName.c_str());
	std::ifstream fin(buf);
	if (fin.is_open())
	{
		fin.close();
		std::cout << "The username has been registered, failed.\n" << std::endl;
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
			std::cout << "The password do not match, please try again." << std::endl;
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

void Controller::registerCourier()
{
	static char buf[30] = { 0 };
	static std::string userName, tmp1, tmp2, tmpPasswd;
	std::cout << "Please input new courier's username (no more than 20 chars):" << std::endl;
	std::cin >> userName;
	if (userName.length() > 20)
	{
		std::cout << "Error: The username is too long, failed.\n" << std::endl;
		return;
	}
	sprintf_s(buf, "key/%s.txt", userName.c_str());
	std::ifstream fin(buf);
	if (fin.is_open())
	{
		fin.close();
		std::cout << "Error: The username has been registered, failed.\n" << std::endl;
		return;
	}
	fin.close();

	// begin to create courier
	while (1)
	{
		std::cout << "Please input new courier's password:" << std::endl;
		std::cin >> tmp1;
		std::cout << "Please input the password again to ensure:" << std::endl;
		std::cin >> tmp2;
		if (tmp1.compare(tmp2) == 0)
			break;
		else
			std::cout << "The password do not match. Try again." << std::endl;
	}
	tmpPasswd = tmp1;
	std::cout << "Please input your telephone number:" << std::endl;
	std::cin >> tmp1;
	
	numberCourier++;
	sprintf_s(buf, "data/Courier%d.txt", numberCourier);
	courier[numberCourier] = Courier(numberCourier, userName, buf, tmpPasswd, tmp1);

	saveInfo();
	courier[numberCourier].save();
	std::cout << "Register successfully!" << std::endl;
}

void Controller::deleteCourier(int courierId)
{
	static char buf[30] = { 0 };
	if (numberCourier <= 1)
	{
		std::cout << "[Controller::deleteCourier()]Error: number of couriers cannot be less than 1, failed.\n" << std::endl;
		return;
	}
	if (courierId<1 || courierId>numberCourier)
	{
		std::cout << "[Controller::deleteCourier()]Error: given [courierId] is invalid, failed.\n" << std::endl;
		return;
	}

	//delete relative files
	sprintf_s(buf, "data/Courier%d.txt", numberCourier);
	remove(buf);
	
	sprintf_s(buf, "key/%s.txt", courier[courierId].getName().c_str());
	remove(buf);

	//change relative packages information
	for (int i = courierId; i < numberCourier; i++)
		courier[i] = courier[i + 1];
	for (int i = 1,j; i <= numberPackage; i++)
	{
		if ((j = package[i]->getPass()) > courierId)
			package[i]->modifyPassId(j - 1);
		else if ((package[i]->getPass()) == courierId)
			package[i]->modifyPassId(1);
	}
	numberCourier--;
	std::cout << "Delete courier operation done.\n" << std::endl;
}

void Controller::sendNewPackage(int type, int volume, int from, int to)
{
	if (numberPackage > MAX_PACKAGE)
	{
		std::cout << "[Controller::sendNewPackage()]Error: no space for new package, failed.\n" << std::endl;
		return;
	}
	++numberPackage;
	static int pass_id = rand() % numberCourier + 1;
	switch (type)
	{
	case FRAGILE:
		package[numberPackage] = new Fragile(type, volume, numberPackage, PACKAGE_READY, from, pass_id, to);
		break;
	case BOOK:
		package[numberPackage] = new Book(type, volume, numberPackage, PACKAGE_READY, from, pass_id, to);
		break;
	case NORMALPACKAGE:
		package[numberPackage] = new Normalpack(type, volume, numberPackage, PACKAGE_READY, from, pass_id, to);
		break;
	}
	package[numberPackage]->send(from);
	static int fee = package[numberPackage]->getPrice();
	user[from].recharge(-fee);
	admin->recharge(fee);
	user[from].appendSend(numberPackage);
	user[to].appendRecv(numberPackage);
	std::cout << "[Controller::sendNewPackage()]package assigned to Courier " << pass_id << ".\n" << std::endl;
}

void Controller::reAssignPackage(int packageId, int pass)
{
	if (1 <= packageId && packageId <= numberPackage)
	{
		if(package[packageId]->getStatus()==PACKAGE_READY)
			package[packageId]->modifyPassId(pass);
		else
		{
			std::cout << "[Controller::reAssignPackage()]Error: the package has been picked, failed." << std::endl;
		}
	}
}

void Controller::pickPackage(int packageId, int pass)
{
	if (1 <= packageId && packageId <= numberPackage)
	{
		package[packageId]->pick(pass);
		static int fee = package[packageId]->getPrice();
		admin->recharge(-0.5 * fee);
		courier[pass].recharge(0.5 * fee);
	}
}

void Controller::recvPackage(int packageId, int to)
{
	if (1 <= packageId && packageId <= numberPackage)
		package[packageId]->recv(to);
}
