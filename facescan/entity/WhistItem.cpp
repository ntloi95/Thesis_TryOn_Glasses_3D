#include "WhistItem.h"
void WhistItem::Init(char userID[], char glassesID[])
{
	strcpy(mUserID, userID);
	strcpy(mGlassID, glassesID);
}