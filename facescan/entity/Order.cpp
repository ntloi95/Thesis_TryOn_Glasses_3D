#include "Order.h"

void Order::Init(char glassesID[], char transactionID[], int number)
{
	strcpy(mGlassID, glassesID);
	strcpy(mTransactionID, mTransactionID);
	mNumber = number;
}