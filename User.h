#ifndef USER_H
#define USER_H

#include <list>
#include <string>
#include "Human.h"

class User : public Human {
private:
    int sendNum, recvNum;
    std::string addr;
    std::list<int> send, recv;

public:
    User(std::string _fileName) :Human(_fileName) { init(); }
    int init(std::string file);
    int init();
    friend std::istream& operator >> (std::istream& in, User& A);
    friend std::ostream& operator << (std::ostream& out, User& A);
};

#endif