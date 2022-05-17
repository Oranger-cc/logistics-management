#include "Package.h"
#include <fstream>

Package::Package(const int _id = 0, const int _status = 0, const int _fromId = 0, const int _toId = 0)
{
	id = _id;
	status = _status;
	fromId = _fromId;
	toId = _toId;
}

int Package::init(const std::string fileName)
{
	std::ifstream fin(fileName);
	if (!fin)
	{
		std::cerr << "ERROR: Failed to open file " << fileName << std::endl;
		return OPEN_FILE_FAIL;
	}
	fin >> (*this);
	return OPEN_FILE_SUCCESS;
}

std::istream& operator>>(std::istream& in, Package& A)
{
	in >> A.id >> A.status >> A.fromId >> A.toId;
	return in;
}

std::ostream& operator<<(std::ostream& out, Package& A)
{
	out << A.id << ' ' << A.status << ' ' << A.fromId << ' ' << A.toId << std::endl;
	return out;
}
