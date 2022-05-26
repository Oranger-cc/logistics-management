#include "Package.h"
#include <fstream>

Package::Package(const int _type = 0, const int _volume = 0, const int _id = 0, const int _status = 0, const int _fromId = 0, const int _passId = 0, const int _toId = 0)
{
	type = _type;
	volume = _volume;
	id = _id;
	status = _status;
	fromId = _fromId;
	passId = _passId;
	toId = _toId;
	fileName = "data/Package" + std::to_string(id) + ".txt";
}

Package::Package(std::string _fileName)
{
	fileName = _fileName;
	//init(fileName);
}

int Package::getType()
{
	return type;
}

int Package::getFrom()
{
	return fromId;
}

int Package::getPass()
{
	return passId;
}

int Package::getTo()
{
	return toId;
}

int Package::getStatus()
{
	return status;
}

void Package::modifyPassId(int newPassId)
{
	passId = newPassId;
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
		std::cout << "[Package::init(string)]Error: Failed to open file " << _fileName << std::endl;
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
		std::cout << "[Package::save()]Error: filename of package " << id << " is empty, failed.\n" << std::endl;
		return 1;
	}
	std::ofstream fout(fileName);
	fout << (*this);
	fout.close();
	return 0;
}

void Package::send(int send_id)
{
	if (fromId == send_id && status == PACKAGE_READY)
	{
		st.set();
	}
	else if (fromId != send_id)
		std::cout << "[Package::send()]Error: this is not your package." << std::endl;
	else
		std::cout << "[Package::send()]Error: the package has been picked or received." << std::endl;
}

void Package::pick(int pick_id)
{
	if (passId == pick_id && status == PACKAGE_READY)
	{
		status = PACKAGE_PICKED;
	}
	else if (passId != pick_id)
		std::cout << "[Package::pick()]Error: this is not your package." << std::endl;
	else
		std::cout << "[Package::pick()]Error: the package has been picked or received." << std::endl;
}

void Package::recv(int recv_id)
{
	if (toId == recv_id && status == PACKAGE_PICKED)
	{
		status = PACKAGE_RECEIVED;
		rt.set();
	}
	else if (toId != recv_id)
		std::cout << "[Package::recv()]Error: this is not your package." << std::endl;
	else
		std::cout << "[Package::pick()]Error: the package has not been picked yet." << std::endl;
}

//int Package::permit(int user_id)
//{
//	return user_id == 0 || user_id == fromId || user_id == toId;
//}

std::istream& operator>>(std::istream& in, Package& A)
{
	in >> A.type >> A.volume;
	in >> A.id >> A.status >> A.fromId >> A.passId >> A.toId;
	in >> A.st >> A.rt;
	return in;
}

std::ostream& operator<<(std::ostream& out, Package& A)
{
	out << A.type << ' ' << A.volume << std::endl;
	out << A.id << ' ' << A.status << ' ' << A.fromId << ' ' << A.passId << ' ' << A.toId << std::endl;
	out << A.st << A.rt << std::endl;
	return out;
}
