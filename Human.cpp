#include "human.h"
#include <iostream>
#include <fstream>

Human::Human(std::string _fileName)
{
    fileName = _fileName;
    //init(fileName);
}

int Human::getId()
{
    return id;
}

int Human::getBla()
{
    return bla;
}

std::string Human::getTel()
{
    return tel;
}

std::string Human::getName()
{
    return name;
}

/*std::istream& operator >> (std::istream& in, Human& A)
{
    in >> A.id >> A.bla >> A.name >> A.tel >> A.passwd;
    return in;
}

std::ostream& operator << (std::ostream& out, Human& A)
{
    out << A.id << '\n';
    out << A.bla << '\n';
    out << A.name << '\n';
    out << A.tel << '\n';
    out << A.passwd << '\n';
    return out;
}*/

int Human::checkPasswd(const std::string newPasswd)
{
    if (newPasswd.length() == 0)
        return EMPTY_PASSWD;
    if (passwd == newPasswd)
        return EQUAL_TO_OLD_PASSWD;
    return VALID_NEW_PASSWD;
}

int Human::modifyPasswd(const std::string newPasswd)
{
    int response = checkPasswd(newPasswd);
    switch (response)
    {
    case VALID_NEW_PASSWD:
        passwd = newPasswd;
        std::cerr << "Your password has been sucessfully updated!\n";
        break;
    case EMPTY_PASSWD:
        std::cerr << "Password can not be empty! Failed.\n";
        break;
    case EQUAL_TO_OLD_PASSWD:
        std::cerr << "Password are equal to the old one! Failed.\n";
        break;
    }
    return response;
}

int Human::modifyFileName(std::string file)
{
    fileName = file;
    return 0;
}