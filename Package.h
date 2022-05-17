#ifndef PACKAGE_H
#define PACKAGE_H

#include <iostream>
#include <string>

#define PACKAGE_READY 0
#define PACKAGE_RECEIVED 1

#define OPEN_FILE_SUCCESS 0
#define OPEN_FILE_FAIL 1

class Package {

private:
	int id,status,fromId,toId;

public:
	Package(int _id, int _status, int _fromId, int _toId);
	int init(const std::string fileName);
	friend std::istream& operator >> (std::istream& in, Package& A);
	friend std::ostream& operator << (std::ostream& out, Package& A);
};

#endif

