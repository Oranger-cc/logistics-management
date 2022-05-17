#ifndef HUMAN_H
#define HUMAN_H

#include <string>

#define VALID_NEW_PASSWD 0
#define EMPTY_PASSWD 1
#define EQUAL_TO_OLD_PASSWD 2

#define OPEN_FILE_SUCCESS 0
#define OPEN_FILE_FAIL 1

class Human {
protected:
    int id, bla;
    std::string name, tel, passwd, fileName;

public:
    Human() {}
    Human(std::string _fileName);
    virtual ~Human() {}
    int getId();
    int getBla();
    std::string getTel();
    std::string getName();
    virtual int init(std::string file) = 0;
    int checkPasswd(const std::string newPasswd);
    int modifyPasswd(const std::string newPasswd);
    int modifyFileName(const std::string file);
    //friend std::istream& operator >> (std::istream& in, Human& A);
    //friend std::ostream& operator << (std::ostream& out, Human& A);
};

/*
id bla
name
tel
passwd
*/

#endif

