#ifndef _WHIST_ITEM_
#define _WHIST_ITEM_
#include <string.h>

class WhistItem{
public:
	char mGlassID[10];
	char mUserID[10];

	void Init(char glassID[], char userID[]);
};

#endif