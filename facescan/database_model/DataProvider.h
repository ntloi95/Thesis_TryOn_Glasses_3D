/*
This class use as a Base to read/write all tables  in Database
Other Database Entity class will inherit this class
*/

#ifndef _DATAPROVIDER_
#define _DATAPROVIDER_
#include "string.h"

class DataProvider
{
public:
	static char mConnectionString[500];
	//connection sql;
	//connection adapter;
	//connection mCommandString;
	void Connect();
	void Disconnect();
	// ExecuteQuery(char sqlString[]);
	// ExecuteNonQuery(char sqlString[]);
	// GetDataFromRow(table, row);
};


#endif