#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Human.h"
#include "User.h"

#define LOGIN_SUCCESS 0
#define LOGIN_FAIL 1

class Account
{
private:
	Human* p;
public:
	Account();
	~Account();
	int regist(std::string userName);
	int login(std::string userName);
};

#endif