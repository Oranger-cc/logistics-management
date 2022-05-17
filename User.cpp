#include "User.h"
#include <iostream>
#include <fstream>

int User::init(const std::string file)
{
    std::ifstream fin(file);
    if (!fin)
    {
        std::cerr << "ERROR: Failed to open file " << file << std::endl;
        return OPEN_FILE_FAIL;
    }
    fin >> (*this);
    return OPEN_FILE_SUCCESS;
}

int User::init()
{
    return init(fileName);
}

std::istream& operator>>(std::istream& in, User& A)
{
    in >> A.id >> A.bla >> A.name >> A.tel >> A.passwd;
    in >> A.addr;
    
    int t;
    A.send.clear();
    in >> A.sendNum;
    for (int i = 1; i <= A.sendNum; i++)
    {
        in >> t;
        A.send.push_back(t);
    }
    A.recv.clear();
    in >> A.recvNum;
    for (int i = 1; i <= A.recvNum; i++)
    {
        in >> t;
        A.recv.push_back(t);
    }
    return in;
}

std::ostream& operator << (std::ostream& out, User& A)
{
    out << A.id << '\n';
    out << A.bla << '\n';
    out << A.name << '\n';
    out << A.tel << '\n';
    out << A.passwd << '\n';
    out << A.addr << '\n';
    out << A.sendNum << '\n';
    for (auto x : A.send)
        out << x <<' ';
    out << '\n';
    out << A.recvNum << '\n';
    for (auto x : A.recv)
        out << x << ' ';
    out << '\n';
    return out;
}