#include "Package.h"
#include <fstream>

Package::Package(const int _id = 0, const int _status = 0, const int _fromId = 0, const int _toId = 0)
{
	id = _id;
	status = _status;
	fromId = _fromId;
	toId = _toId;
	fileName = "data/Package" + std::to_string(id) + ".txt";
	tm.set();
}

Package::Package(std::string _fileName)
{
	fileName = _fileName;
	init(fileName);
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
	fin.close();
	return OPEN_FILE_SUCCESS;
}

int Package::init()
{
	return init(fileName);
}

int Package::save()
{
	if (fileName.empty())
	{
		std::cout << "Empty filename. Failed.\n" << std::endl;
		return 1;
	}
	std::ofstream fout(fileName);
	fout << (*this);
	fout.close();
	return 0;
}

int Package::eralier_than(Timestamp t)
{
	return tm<t;
}

int Package::later_than(Timestamp t)
{
	return t < tm;
}

int Package::recv(int recv_id)
{
	if (toId == recv_id && status == PACKAGE_READY)
	{
		status = PACKAGE_RECEIVED;
		return 0;
	}
	return 1;
}

std::istream& operator>>(std::istream& in, Package& A)
{
	in >> A.id >> A.status >> A.fromId >> A.toId;
	in >> A.tm;
	return in;
}

std::ostream& operator<<(std::ostream& out, Package& A)
{
	out << A.id << ' ' << A.status << ' ' << A.fromId << ' ' << A.toId << std::endl;
	out << A.tm << std::endl;
	return out;
}
