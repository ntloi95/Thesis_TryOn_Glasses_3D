#ifndef _ORDER_
#define _ORDER_
#include <string.h>

class Order{
public:
	char mGlassID[10];
	char mTransactionID[10];
	int mNumber;

	void Init(char glassesID[], char transactionID[], int number = 1);
};

#endif