#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "Filter.h"

#define VALID_NEW_PASSWD 0
#define EMPTY_PASSWD 1
#define EQUAL_TO_OLD_PASSWD 2

#define OPEN_FILE_SUCCESS 0
#define OPEN_FILE_FAIL 1

class Human {
protected:
    int id;
    double bla;
    std::string name, tel, passwd, fileName; //fileName is as "data/User1.txt"

public:
    Human() {}
    Human(std::string _fileName);
    virtual ~Human() {}
    int getId();
    int getBla();
    void recharge(double ch);
    std::string getTel();
    std::string getName();
    virtual int init(std::string file) = 0;
    virtual int listen()=0;
    int checkPasswd(const std::string newPasswd);
    int modifyPasswd(const std::string newPasswd);
    int modifyFileName(const std::string file);
    //friend std::istream& operator >> (std::istream& in, Human& A);
    //friend std::ostream& operator << (std::ostream& out, Human& A);
};

/*
* id bla
* name
* tel
* passwd
*/

#endif

