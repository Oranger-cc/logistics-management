#include "Fragile.h"

Fragile::Fragile(const int _type = 0, const int _volume = 0, const int _id = 0, const int _status = 0, const int _fromId = 0, const int _passId = 0, const int _toId = 0)
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

Fragile::Fragile(std::string _fileName)
{
    init(_fileName);
}

int Fragile::getPrice()
{
    if (type == FRAGILE)
    {
        return volume*8;
    }
    std::cout << "[Fragile::getPrice()]Error: wrong item type." << std::endl;
    return 0;
}
