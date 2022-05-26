#include "Book.h"

Book::Book(const int _type = 0, const int _volume=0, const int _id = 0, const int _status = 0, const int _fromId = 0, const int _passId = 0, const int _toId = 0)
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

Book::Book(std::string _fileName)
{
    init(_fileName);
}

int Book::getPrice()
{
    if (type == BOOK)
    {
        return volume * 2;
    }
    std::cout << "[Book::getPrice()]Error: wrong item type." << std::endl;
    return 0;
}
