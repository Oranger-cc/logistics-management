#include "Filter.h"

void Filter::init(const std::vector<int>& Arr)
{
	static char buf[30];
	ele.clear();
	for (auto x : Arr)
	{
		sprintf_s(buf, "data/Package%d.txt", x);
		Package t(buf);
		ele.push_back(t);
	}
}

void Filter::filter(Timestamp time_low, Timestamp time_up, const int id = -1)
{
	int cnt = 0;
	if (~id)
	{
		char buf[30];
		sprintf_s(buf, "data/Package%d.txt", id);
		Package tar(buf);
		if (!tar.eralier_than(time_low) && !tar.later_than(time_up))
		{
			++cnt;
			std::cout << tar;
		}
	}
	else
	{
		for (auto x : ele)
		{
			if (x.eralier_than(time_low))
				continue;
			if (x.later_than(time_up))
				break;
			std::cout << x;
		}
	}
	std::cout << cnt << " packages found. Done.\n" << std::endl;
}


