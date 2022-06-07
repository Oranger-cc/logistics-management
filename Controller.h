#pragma once

#include <string>
#include "User.h"
#include "Admin.h"
#include "Courier.h"
#include "Human.h"
#include "Fragile.h"
#include "Book.h"
#include "Normalpack.h"
#include "Package.h"
#include "Filter.h"

#define MAX_USER 10000
#define MAX_COURIER 10000
#define MAX_PACKAGE 10000

class Controller
{
public:
	int numberUser, numberPackage, numberCourier;
	User* user;
	Admin* admin; // only Admin's ID is 0
	Courier* courier;
	Package* package[MAX_PACKAGE];
	Human* p; //current account
	Filter* ft;

	Controller();
	~Controller();
	int saveInfo();
	int login(std::string userName);
	int regist();
	void registerCourier();
	void deleteCourier(int courierId);
	void sendNewPackage(int type, int volume, int from, int to);
	void reAssignPackage(int packageId, int pass);
	void pickPackage(int packageId, int pass);
	void recvPackage(int packageId, int to);
};

