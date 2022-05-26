#pragma once
#include "Package.h"
class Fragile :
    public Package
{
public:
    Fragile(int _type, int _volume, int _id, int _status, int _fromId, int _passId, int _toId);
    Fragile(std::string _fileName);
    int getPrice();
};

