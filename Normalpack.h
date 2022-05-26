#pragma once
#include "Package.h"
class Normalpack :
    public Package
{
public:
    Normalpack(int _type, int _volume, int _id, int _status, int _fromId, int _passId, int _toId);
    Normalpack(std::string _fileName);
    int getPrice();
};

