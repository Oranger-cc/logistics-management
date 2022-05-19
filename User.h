#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include "Human.h"
#include "Package.h"

class User : public Human {
private:
    int sendNum, recvNum;
    std::string addr;
    std::vector<int> send, recv;

public:
    User() {}
    User(std::string _fileName) :Human(_fileName) { init(); }
    User(int _id, std::string _name, std::string _fileName, std::string _passwd, std::string _tel, std::string _addr);
    int init(std::string _fileName);
    int init();
    int save();
    int listen(); 
    void appendSend(const int& packId);
    void appendRecv(const int& packId);
    friend std::istream& operator >> (std::istream& in, User& A);
    friend std::ostream& operator << (std::ostream& out, User& A);
};

#endif