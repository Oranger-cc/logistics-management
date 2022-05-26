#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "Package.h"

class Filter
{
private:
	//std::vector<Package> ele;
public:
	Filter() {}
	//void config(const std::vector<int>&);
	//void config(const int n);
	void uFilter();
	void cFilter();
	void pFilterById(int userId, int id);
	void pFilterBySendTime(int userId, Timestamp low, Timestamp up);
	void pFilterByRecvTime(int userId, Timestamp low, Timestamp up);
	void pFilterByUser(int userId, int id);
	void pFilterByCourierId(int courierId, int id);
	void pFilterCourier(int courierId, int sendId, int recvId, int sta);
	//void pfilter(Timestamp low, Timestamp up, int id);
};

#endif
