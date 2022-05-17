#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Human.h"
#include "User.h"

#define LOGIN_SUCCESS 0
#define LOGIN_FAIL 1

#define REGISTER_SUCCESS 0
#define REGISTER_FAIL 1

class Account
{
private:
	int numberUser, numberPackage;
	Human* p;
public:
	Account();
	~Account();
	int login(std::string userName);
	int regist();
};

#endif