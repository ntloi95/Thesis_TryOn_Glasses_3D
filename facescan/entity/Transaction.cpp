#include "Transaction.h"

void Transaction::Init(char ID[], char userID[])
{
	strcpy(mID, ID);
	strcpy(mUserID, userID);
}