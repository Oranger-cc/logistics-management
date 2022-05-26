#include "Courier.h"
#include "Controller.h"
#include <fstream>

extern Controller* now;

Courier::Courier()
{

}

Courier::Courier(int _id, std::string _name, std::string _fileName, std::string _passwd, std::string _tel)
{
    id = _id;
    name = _name;
    fileName = _fileName;
    passwd = _passwd;
    tel = _tel;
    bla = 0;
}

int Courier::init(std::string _fileName)
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

void Courier::save()
{
    static char buf[30] = { 0 };
    if (fileName.empty())
    {
        std::cout << "[Courier::save()]Error: Empty filename." << std::endl;
        return;
    }
    std::ofstream fout(fileName);
    fout << (*this);
    fout.clear();
    fout.close();

    sprintf_s(buf, "key/%s.txt", name.c_str());
    fout.open(buf);
    fout << passwd << std::endl;
    fout << "Courier " << id << std::endl;
    fout.close();
}

int Courier::listen()
{
    int num;
    std::string op, str;
    Timestamp low, up;
    char buf[30] = { 0 };
    while (1)
    {
        std::cout << "==============================\n"
            << "Please choose a way to continue:\n"
            << "mp [old password] [string]: change your password to [string]\n"
            << "b: query your account balance\n"
            << "c [number]: top up your account with [number] yuan\n"
            << "f1 [r/s] [lower timestamp] [upper timestamp] [number]: search specified packages with parameters\n"
            << "f2 [senderID] [receiverID] [packageID] [stauts:0/1/2/3]: search specified packages with parameters\n"
            << "p [number]: pick a package with ID [number]\n"
            << "q: quit\n"
            << "==============================\n" << std::endl;

        std::cin >> op;
        if (op[0] == 'm' && op.length() >= 2 && op[1] == 'p')
        {
            std::cin >> str;
            if (checkPasswd(str) == EQUAL_TO_OLD_PASSWD)
            {
                std::cin >> str;
                modifyPasswd(str);
            }
            else
            {
                std::cin >> str;
                std::cout << "Wrong old password. Failed\n" << std::endl;
            }
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
        else if (op[0] == 'f'&&op.length()>1&&op[1]=='1')
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
                now->ft->pFilterBySendTime(id, low, up);
            }
            else if (str[0] == 'r')
            {
                now->ft->pFilterByRecvTime(id, low, up);
            }
            else
            {
                std::cout << "Error: bad parameters. Failed.\n" << std::endl;
            }
        }
        else if (op[0] == 'f' && op.length() > 1 && op[1] == '2')
        {
            int si, ri, pi;
            std::cin >> si >> ri >> pi >> num;
            if (~pi)
            {
                now->ft->pFilterByCourierId(id, pi);
            }
            else
            {
                now->ft->pFilterCourier(id, si, ri, num);
            }
        }
        else if (op[0] == 'p')
        {
            std::cin >> num;
            now->pickPackage(num,id);
        }
        else if (op[0] == 'q')
        {
            break;
        }
        else
        {
            std::cout << "Error: bad parameters. Please try again.\n" << std::endl;
        }
    }
    return 0;
}

std::istream& operator>>(std::istream& in, Courier& A)
{
    in >> A.id >> A.bla >> A.name >> A.tel >> A.passwd;
    return in;
}

std::ostream& operator<<(std::ostream& out, Courier& A)
{
    out << A.id << std::endl;
    out << A.bla << std::endl;
    out << A.name << std::endl;
    out << A.tel << std::endl;
    out << A.passwd << std::endl;
    return out;
}
