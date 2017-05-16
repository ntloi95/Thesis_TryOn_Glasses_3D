#ifndef _TRANSACTION_
#define _TRANSACTION_
#include <string.h>
class Transaction{
public:
	char mID[10];
	char mUserID[10];

	void Init(char ID[], char userID[]);
};

#endif