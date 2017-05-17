#ifndef _DWHIST_ITEM_
#define _DWHIST_ITEM_
#include "DataProvider.h"
#include "../entity/WhistItem.h"

class DWhistItem : public DataProvider{
public:
	void InsertWhistItem(WhistItem item);
	void DeleteWhistItem(WhistItem item);
	void DeleteWhistItem(char itemID[]);
	void UpdateWhistItem(WhistItem oldItem, WhistItem newItem);
	void UpdatewhistItem(char itemID[], WhistItem newItem);
};

#endif