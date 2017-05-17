#ifndef _DTRANSACTION_
#define _DTRANSACTION_
#include "DataProvider.h"
#include "../entity/Transaction.h"
class DTransaction: public DataProvider{
public:
	void InsertTransaction(Transaction trans);
	void DeleteTransaction(Transaction trans);
	void DeleteTransaction(char transID[]);
	void UpdateTransaction(Transaction oldTrans, Transaction newTrans);
	void UpdateTransaction(char transID[], Transaction newTrans);
};

#endif