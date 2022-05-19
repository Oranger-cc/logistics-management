#pragma once
#include <string>
#include "Human.h"

class Admin :
    public Human
{
public:
    Admin(std::string _fileName) :Human(_fileName) {}
    int init(std::string _fileName);
    int init();
    int save();
    int listen();
    friend std::istream& operator >> (std::istream& in, Admin& A);
    friend std::ostream& operator << (std::ostream& out, Admin& A);
};

