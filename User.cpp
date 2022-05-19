#include "User.h"
#include <iostream>
#include <fstream>
#include "Controller.h"

extern Controller* now;

User::User(int _id, std::string _name, std::string _fileName, std::string _passwd, std::string _tel, std::string _addr)
{
    id = _id;
    name = _name;
    fileName = _fileName;
    passwd = _passwd;
    tel = _tel;
    addr = _addr;
    bla = 0;
    sendNum = recvNum = 0;
    send.clear();
    recv.clear();
}

int User::init(const std::string _fileName)
{
    std::ifstream fin(_fileName);
    if (!fin)
    {
        std::cout << "ERROR: Failed to open file " << _fileName << std::endl;
        return OPEN_FILE_FAIL;
    }
    fileName = _fileName;
    fin >> (*this);
    fin.close();
    return OPEN_FILE_SUCCESS;
}

int User::init()
{
    return init(fileName);
}

int User::save()
{
    static char buf[30] = { 0 };
    if (fileName.empty())
    {
        std::cout << "Empty filename. Failed.\n" << std::endl;
        return 1;
    }
    std::ofstream fout(fileName);
    fout << (*this);
    fout.clear();
    fout.close();
    
    sprintf_s(buf, "key/%s.txt", name.c_str());
    fout.open(buf);
    fout << passwd << std::endl;
    fout << "User " << id << std::endl;
    fout.close();
    return 0;
}

int User::listen()
{
    int num;
    std::string op,str;
    Timestamp low, up;
    char buf[30]={0};
    while (1)
    {
        std::cout << "==============================\n"
            << "Please choose a way to continue:\n"
            << "mp [string]: change your password to [string]\n"
            << "b: query your account balance\n"
            << "c [number]: top up your account with [number] yuan\n"
            << "f [r/s] [lower timestamp] [upper timestamp] [number]: search specified packages with parameters\n"
            << "s [number]: send a package to user with ID [number]\n"
            << "r [number]: confirm receipt of your package of ID [number]\n"
            << "q: quit\n" 
            << "==============================\n" << std::endl;
        
        std::cin >> op;
        if (op[0] == 'm'&&op.length() >= 2 && op[1] == 'p')
        {
            std::cin >> str;
            modifyPasswd(str);
        }
        else if (op[0] == 'b')
        {
            std::cout << "The balance in your account: " << bla << std::endl;
        }
        else if (op[0] == 'c')
        {
            std::cin >> num;
            if (num >= 0)
            {
                recharge(num);
                std::cout << "Done.\n" << std::endl;
            }
            else
            {
                std::cout << "Input should be a positive integer. Failed.\n" << std::endl;
            }
        }
        else if (op[0] == 'f')
        {
            /*
            * The [number] field has the highest priority,
            * followed by [lower timestamp], [upper timestamp] and [r/s]
            */
            std::cin >> str >> low >> up >> num;
            if (~num)
            {
                now->ft->pFilterById(id, num);
            }
            else if (str[0] == 's')
            {
                now->ft->pFilterBySendTime(id,low,up);
            }
            else if (str[0] == 'r')
            {
                now->ft->pFilterByRecvTime(id, low, up);
            }
            else
            {
                std::cout << "Bad parameters. Failed.\n" << std::endl;
            }
        }
        else if (op[0] == 's')
        {
            //std::cout << "Please input the ID of the receiver:" << std::endl;
            std::cin >> num;
            if (1 <= num && num <= (now->numberUser) && num != id)
            {
                now->sendNewPackage(id, num);
                std::cout << "Done.\n" << std::endl;
            }
            else
            {
                std::cout << "Invalid receiver ID. Failed.\n" << std::endl;
            }
        }
        else if (op[0] == 'r')
        {
            std::cin >> num;
            if (now->recvPackage(num, id) == 0)
            {
                std::cout << "Done.\n" << std::endl;
            }
            else
            {
                std::cout << "Failed to receive.\n" << std::endl;
            }
        }
        else if (op[0] == 'q')
        {
            break;
        }
        else
        {
            std::cout << "Invalid input, try again." << std::endl;
        }
    }
    return 0;
}

void User::appendSend(const int& packId)
{
    sendNum++;
    send.push_back(packId);
}

void User::appendRecv(const int& packId)
{
    recvNum++;
    recv.push_back(packId);
}

std::istream& operator>>(std::istream& in, User& A)
{
    in >> A.id >> A.bla >> A.name >> A.tel >> A.passwd;
    in >> A.addr;
    
    int t;
    A.send.clear();
    in >> A.sendNum;
    for (int i = 1; i <= A.sendNum; i++)
    {
        in >> t;
        A.send.push_back(t);
    }
    A.recv.clear();
    in >> A.recvNum;
    for (int i = 1; i <= A.recvNum; i++)
    {
        in >> t;
        A.recv.push_back(t);
    }
    return in;
}

std::ostream& operator << (std::ostream& out, User& A)
{
    out << A.id << std::endl;
    out << A.bla << std::endl;
    out << A.name << std::endl;
    out << A.tel << std::endl;
    out << A.passwd << std::endl;
    out << A.addr << std::endl;
    out << A.sendNum << std::endl;
    for (auto x : A.send)
        out << x <<' ';
    out << std::endl;
    out << A.recvNum << std::endl;
    for (auto x : A.recv)
        out << x << ' ';
    out << std::endl;
    return out;
}