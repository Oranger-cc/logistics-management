#include "Filter.h"
#include "Controller.h"

extern Controller* now;
/*
void Filter::config(const std::vector<int>& Arr)
{
	static char buf[30] = { 0 };
	static Package t;
	ele.clear();
	for (auto x : Arr)
	{
		sprintf_s(buf, "data/Package%d.txt", x);
		t.init(buf);
		ele.push_back(t);
	}
}

void Filter::config(const int n)
{
	static char buf[30] = { 0 };
	static Package t;
	ele.clear();
	for (int i = 1; i <= n; i++)
	{
		sprintf_s(buf, "data/Package%d.txt", x);
		t.init(buf);
		ele.push_back(t);
	}
}
*/

void Filter::uFilter()
{
	for (int i = 1; i <= (now->numberUser); i++)
	{
		std::cout << (now->user[i]);
	}
	std::cout << now->numberUser << " users found. Done.\n" << std::endl;
}

void Filter::pFilterById(int userId, int id)
{
	int cnt = 0;
	if (1 <= id && id <= (now->numberPackage)&&now->package[id].permit(userId))
	{
		cnt++;
		std::cout << now->package[id];
	}
	std::cout << cnt << " packages found. Done.\n" << std::endl;
}

void Filter::pFilterBySendTime(int userId, const Timestamp low=Timestamp(0,0,0,0,0,0), const Timestamp up=Timestamp(9999,0,0,0,0,0))
{
	int cnt = 0;
	for (int i = 1; i <= (now->numberPackage); i++)
	{
		if (now->package[i].getSendTime() < low)
			continue;
		if (up < now->package[i].getSendTime())
			break;
		if (now->package[i].getFrom()==userId)
		{
			cnt++;
			std::cout << now->package[i];
		}
	}
	std::cout << cnt << " packages found. Done.\n" << std::endl;
}

void Filter::pFilterByRecvTime(int userId, const Timestamp low = Timestamp(0, 0, 0, 0, 0, 0), const Timestamp up = Timestamp(9999, 0, 0, 0, 0, 0))
{
	int cnt = 0;
	for (int i = 1; i <= (now->numberPackage); i++)
	{
		if (now->package[i].getSendTime() < low)
			continue;
		if (up < now->package[i].getSendTime())
			break;
		if (now->package[i].getTo()==userId)
		{
			cnt++;
			std::cout << now->package[i];
		}
	}
	std::cout << cnt << " packages found. Done.\n" << std::endl;
}

void Filter::pFilterByUser(int userId, int id)
{
	int cnt = 0;
	for (int i = 1; i <= (now->numberPackage); i++)
	{
		if (now->package[i].permit(userId))
		{
			cnt++;
			std::cout << now->package[i];
		}
	}
	std::cout << cnt << " packages found. Done.\n" << std::endl;
}

