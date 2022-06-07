#include "Admin.h"
#include <fstream>
#include "Controller.h"

extern Controller* now;

int Admin::init(std::string _fileName)
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

int Admin::init()
{
    return init(fileName);
}

int Admin::save()
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
    fout << "Admin " << id << std::endl;
    fout.close();
    return 0;
}

int Admin::listen()
{
    int num, user_id;
    std::string op, str;
    Timestamp low, up;
    char buf[30]={0};
    while (1)
    {
        std::cout << "==============================\n"
            << "Please choose a way to continue:\n"
            << "mp [string]: change your password to [string]\n"
            << "b: query your account balance\n"
            << "a: add a new courier\n"
            << "d [courier_id]: delete the courier with [courier_id]\n"
            << "r [package_id] [courier_id]: re-assign [package_id] to [courier_id]\n"
            << "f1 [user id] [r/s] [lower timestamp] [upper timestamp] [number]: search specified packages with parameters\n"
            << "f2 [courier_id] [senderID] [receiverID] [packageID] [stauts:0/1/2/3]:\n"
            << "    search specified packages with parameters, note [courier_id] cannot be empty\n"
            << "u: show all users' profile\n"
            << "c: show all couriers' profile\n"
            << "q: quit\n"
            << "==============================\n" << std::endl;

        std::cin >> op;
        if (op[0] == 'm' && op.length() >= 2 && op[1] == 'p')
        {
            std::cin >> str;
            modifyPasswd(str);
        }
        else if (op[0] == 'b')
        {
            std::cout << "The balance in your account: " << bla << std::endl;
        }
        else if (op[0] == 'a')
        {
            now->registerCourier();
        }
        else if (op[0] == 'd')
        {
            std::cin >> num;
            now->deleteCourier(num);
        }
        else if (op[0] == 'r')
        {
            int pi, ci;
            std::cin >> pi >> ci;
            now->reAssignPackage(pi, ci);
        }
        else if (op[0] == 'f' && op.length() > 1 && op[1] == '1')
        {
            /*
            * The [number] field has the highest priority,
            * followed by [r/s] [lower timestamp], [upper timestamp] and [user id]
            */
            std::cin >> user_id >> str >> low >> up >> num;
            if (~num)
            {
                now->ft->pFilterById(user_id, num);
            }
            else if (str[0] == 's')
            {
                now->ft->pFilterBySendTime(user_id, low, up);
            }
            else if (str[0] == 'r')
            {
                now->ft->pFilterByRecvTime(user_id, low, up);
            }
            else
            {
                std::cout << "Bad parameters, failed.\n" << std::endl;
            }
        }
        else if (op[0] == 'f' && op.length() > 1 && op[1] == '2')
        {
            int ci, si, ri, pi;
            std::cin >> ci >> si >> ri >> pi >> num;
            if (~pi)
            {
                now->ft->pFilterById(0, pi);
            }
            else
            {
                now->ft->pFilterCourier(ci, si, ri, num);
            }
        }
        else if (op[0] == 'u')
        {
            now->ft->uFilter();
        }
        else if (op[0] == 'c')
        {
            now->ft->cFilter();
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

std::istream& operator>>(std::istream& in, Admin& A)
{
    in >> A.id >> A.bla >> A.name >> A.tel >> A.passwd;
    return in;
}

std::ostream& operator << (std::ostream& out, Admin& A)
{
    out << A.id << std::endl;
    out << A.bla << std::endl;
    out << A.name << std::endl;
    out << A.tel << std::endl;
    out << A.passwd << std::endl;
    return out;
}