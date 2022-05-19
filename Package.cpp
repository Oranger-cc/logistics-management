#include "Package.h"
#include <fstream>

Package::Package(const int _id = 0, const int _status = 0, const int _fromId = 0, const int _toId = 0)
{
	id = _id;
	status = _status;
	fromId = _fromId;
	toId = _toId;
	fileName = "data/Package" + std::to_string(id) + ".txt";
}

Package::Package(std::string _fileName)
{
	fileName = _fileName;
	//init(fileName);
}

int Package::getFrom()
{
	return fromId;
}

int Package::getTo()
{
	return toId;
}

Timestamp Package::getSendTime()
{
	return st;
}

Timestamp Package::getRecvTime()
{
	return rt;
}

int Package::init(const std::string _fileName)
{
	std::ifstream fin(_fileName);
	if (!fin)
	{
		std::cout << "ERROR: Failed to open file " << _fileName << std::endl;
		return OPEN_FILE_FAIL;
	}
	fileName = _fileName;
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

int Package::send(int send_id)
{
	if (fromId == send_id && status == PACKAGE_READY)
	{
		st.set();
		return 0;
	}
	return 1;
}

int Package::recv(int recv_id)
{
	if (toId == recv_id && status == PACKAGE_READY)
	{
		status = PACKAGE_RECEIVED;
		rt.set();
		return 0;
	}
	return 1;
}

int Package::permit(int user_id)
{
	return user_id == 0 || user_id == fromId || user_id == toId;
}

std::istream& operator>>(std::istream& in, Package& A)
{
	in >> A.id >> A.status >> A.fromId >> A.toId;
	in >> A.st >> A.rt;
	return in;
}

std::ostream& operator<<(std::ostream& out, Package& A)
{
	out << A.id << ' ' << A.status << ' ' << A.fromId << ' ' << A.toId << std::endl;
	out << A.st << A.rt << std::endl;
	return out;
}
