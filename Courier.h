#pragma once
#include "Human.h"
#include "Package.h"
#include <string>

class Courier :
    public Human
{
public:
    Courier();
    Courier(int _id, std::string _name, std::string _fileName, std::string _passwd, std::string _tel);
    int init(std::string _fileName);
    void save();
    int listen();
    friend std::istream& operator >> (std::istream& in, Courier& A);
    friend std::ostream& operator << (std::ostream& out, Courier& A);
};

