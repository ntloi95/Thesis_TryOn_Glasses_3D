#ifndef _DUSER_
#define _DUSER_
#include "../entity/User.h"
#include "DataProvider.h"

class DUser: public DataProvider {
public:
	void InsertUser(User u);
	void DeleteUser(User u);
	void DeleteUser(char uID[]);
	void UpdateUser(User oldUser, User newUser);
	void UpdateUser(char uID[], User newUser);
};

#endif