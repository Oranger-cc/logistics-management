#pragma once

#include <string>
#include "Human.h"
#include "Package.h"
#include "User.h"
#include "Admin.h"
#include "Filter.h"

#define MAX_USER 10000
#define MAX_PACKAGE 10000

class Controller
{
public:
	int numberUser, numberPackage;
	User* user;
	Admin* admin; // only Admin's ID is 0
	Package* package;
	Human* p; //current account
	Filter* ft;

	Controller();
	~Controller();
	int saveInfo();
	int login(std::string userName);
	int regist();
	int sendNewPackage(int from, int to);
	int recvPackage(int packageId, int to);
};

