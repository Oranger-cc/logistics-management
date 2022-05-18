#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <fstream>

class Timestamp
{
private:
	int year, month, day, hour, minute, second;
public:
	Timestamp(int,int,int,int,int,int);
	Timestamp() :Timestamp(0, 0, 0, 0, 0, 0) {}
	void set();
	bool operator == (const Timestamp& t)const;
	bool operator < (const Timestamp& t)const;
	bool operator <= (const Timestamp& t)const;
	friend std::istream& operator >> (std::istream& in, Timestamp& A);
	friend std::ostream& operator << (std::ostream& out, Timestamp& A);
};

#endif