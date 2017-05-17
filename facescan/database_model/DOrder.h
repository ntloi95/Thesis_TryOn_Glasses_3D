#ifndef _DORDER_
#define _DORDER_
#include "DataProvider.h"
#include "../entity/Order.h"

class DOrder : public DataProvider{
public:
	void InsertOrder(Order order);
	void DeleteOrder(Order order);
	void DeleteOrder(char orderID[]);
	void UpdateOrder(Order oldOrder, Order newOrder);
	void UpdateOrder(char orderID[], Order newOrder);
};

#endif