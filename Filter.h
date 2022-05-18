#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "Package.h"

class Filter
{
private:
	std::vector<Package> ele;
public:
	void init(const std::vector<int>&);
	void filter(Timestamp time_low,Timestamp time_up,int id);
};

#endif
