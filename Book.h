#pragma once
#include "Package.h"
class Book :
    public Package
{
public:
    Book(int _type, int _volume, int _id, int _status, int _fromId, int _passId, int _toId);
    Book(std::string _fileName);
    int getPrice();
};

