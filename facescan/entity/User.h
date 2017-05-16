#ifndef _USER_
#define _USER_
#include <string.h>
#define MALE 0
#define FEMALE 1
class User{
public:
	char mID[10];
	char mName[50];
	char mEmail[50];
	char mAddress[256];
	char mDiscription[256];
	bool mGender;

	void Init(char ID[], char name[] = "Jose Mourinho", char email[] = "tryonglass@internet.com", char address[] = "1, Nguyen Van Cu St., Dis. 5, Ho Chi Minh City", bool gender = MALE, char discription[] = "This is discription");
};

#endif