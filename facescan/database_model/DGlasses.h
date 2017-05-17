/*
This class use to read/write table Glasses in Database
*/

#ifndef _DGLASSES_
#define _DGLASSES_
#include "../entity/Glasses.h"
#include "DataProvider.h"

class DGlasses : public DataProvider
{
public:
	void InsertGlasses(Glasses g);
	void DeleteGlasses(Glasses g);
	void DeleteGlasses(char GlassesID[]);
	void UpdateGlasses(Glasses oldGlasses, Glasses newGlasses);
	void UpdateGlasses(char oldGlassesID, Glasses newGlasses);
};


#endif