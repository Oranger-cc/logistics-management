#include "User.h"
#include <iostream>
#include <fstream>

User::User(int _id, std::string _name, std::string _fileName)
{
    std::string tmp;
    id = _id;
    name = _name;
    fileName = _fileName;
    bla = sendNum = recvNum = 0;
    send.clear();
    recv.clear();
    while(1)
    {
        std::cout << "Please input your password:" << std::endl;
        std::cin >> passwd;
        std::cout << "Please input your password again to ensure:" << std::endl;
        std::cin >> tmp;
        if (passwd.compare(tmp) == 0)
            break;
        else
            std::cout << "The password do not match. Try again." << std::endl;
    }
    std::cout << "Please input your telephone number:" << std::endl;
    std::cin >> tel;
    std::cout << "Please input your location:" << std::endl;
    std::cin >> addr;
    save();
    std::cout << "Register successfully!" << std::endl;
}

int User::init(const std::string file)
{
    std::ifstream fin(file);
    if (!fin)
    {
        std::cerr << "ERROR: Failed to open file " << file << std::endl;
        return OPEN_FILE_FAIL;
    }
    fin >> (*this);
    fin.close();
    return OPEN_FILE_SUCCESS;
}

int User::init()
{
    return init(fileName);
}

int User::save()
{
    static char buf[30] = { 0 };
    std::ofstream fout(fileName);
    fout << (*this);
    fout.clear();
    fout.close();
    
    sprintf_s(buf, "key/%s.txt", name.c_str());
    fout.open(buf);
    fout << passwd << std::endl << fileName << std::endl;
    fout.close();
    return 0;
}

int User::listen()
{
    //
    return 0;
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
    out << A.id << std::endl;
    out << A.bla << std::endl;
    out << A.name << std::endl;
    out << A.tel << std::endl;
    out << A.passwd << std::endl;
    out << A.addr << std::endl;
    out << A.sendNum << std::endl;
    for (auto x : A.send)
        out << x <<' ';
    out << std::endl;
    out << A.recvNum << std::endl;
    for (auto x : A.recv)
        out << x << ' ';
    out << std::endl;
    return out;
}