#ifndef PACKAGE_H
#define PACKAGE_H

#include <iostream>
#include <string>
#include "Timestamp.h"

#define PACKAGE_READY 1
#define PACKAGE_PICKED 2
#define PACKAGE_RECEIVED 3

#define OPEN_FILE_SUCCESS 0
#define OPEN_FILE_FAIL 1

#define FRAGILE 1
#define BOOK 2
#define NORMALPACKAGE 3

class Package {

protected:
	int type, volume;
	int id, status, fromId, passId, toId;
	Timestamp st,rt;
	std::string fileName;

public:
	Package() {}
	Package(int _type, int _volume, int _id, int _status, int _fromId, int _passId, int _toId);//
	Package(std::string _fileName);
	int getType();
	int getFrom();
	int getPass();
	int getTo();
	int getStatus();
	void modifyPassId(int newPassId);
	Timestamp getSendTime();
	Timestamp getRecvTime();
	int init(const std::string _fileName);
	int init();
	int save();
	void send(int send_id);
	void pick(int pick_id);
	void recv(int recv_id);
	//int permit(int user_id);// maybe deleted
	virtual int getPrice() = 0;
	friend std::istream& operator >> (std::istream& in, Package& A);
	friend std::ostream& operator << (std::ostream& out, Package& A);
};

#endif

