#include "User.h"
void User::Init(char ID[], char name[], char email[], char address[], bool gender, char discription[])
{
	strcpy(mID, ID);
	strcpy(mName, name);
	strcpy(mEmail, email);
	strcpy(mAddress, address);
	mGender = gender;
	strcpy(mDiscription, discription);
}