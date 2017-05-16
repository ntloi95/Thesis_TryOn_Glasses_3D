#include "Glasses.h"

Glasses::Glasses(){
	mThumnail[0] = 0;
	mPrice = 0;
	mTemple = 0;
	mEye = 0;
	mBridge = 0;
}

Glasses::~Glasses(){}

void Glasses::Init(char ID[], char name[], char color[], char producer[], float price, char thumnail[], int status, int temple, int eye, int bridge)
{
	strcpy(mID, ID);
	strcpy(mName, name);
	strcpy(mColor, color);
	strcpy(mProducer, producer);
	strcpy(mThumnail, thumnail);
	mPrice = price;
	mStatus = status;
	mTemple = temple;
	mEye = eye;
	mBridge = bridge;
}