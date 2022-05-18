#include "Timestamp.h"
#include <windows.h>

Timestamp::Timestamp(const int _y = 0, const int _mo = 0, const int _d = 0, const int _h=0, const int _mi = 0, const int _s = 0)
{
	year = _y;
	month = _mo;
	day = _d;
	hour = _h;
	minute = _mi;
	second = _s;
}

void Timestamp::set()
{
	SYSTEMTIME now;
	GetLocalTime(&now);
	year = now.wYear;
	month = now.wMonth;
	day = now.wDay;
	hour = now.wHour;
	minute = now.wMinute;
	second = now.wSecond;
}

bool Timestamp::operator==(const Timestamp& t) const
{
	return year == t.year && month == t.month && day == t.day && hour == t.hour && minute == t.minute && second == t.second;
}

bool Timestamp::operator<(const Timestamp& t) const
{
	{
		if (year == t.year)
		{
			if (month == t.month)
			{
				if (day == t.day)
				{
					if (hour == t.hour)
						return minute == t.minute ? second < t.second : minute < t.minute;
					return hour < t.hour;
				}
				return day < t.day;
			}
			return month < t.month;
		}
		return year < t.year;
	}
}

bool Timestamp::operator<=(const Timestamp& t) const
{
	return (*this)<t||(*this)==t;
}

std::istream& operator>>(std::istream& in, Timestamp& A)
{
	in >> A.year >> A.month >> A.day >> A.hour >> A.minute >> A.second;
	return in;
}

std::ostream& operator<<(std::ostream& out, Timestamp& A)
{
	out << A.year << ' ' << A.month << ' ' << A.day << ' ' << A.hour << ' ' << A.minute << ' ' << A.second << std::endl;
	return out;
}
