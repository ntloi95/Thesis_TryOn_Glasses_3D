#ifndef _GLASSES_
#define _GLASSES_
#include <string.h>
using namespace std;
const char STATUS[][10] = { "Available", "Sale off", "Sold out", "Waitting" };
#define AVAILABLE 0
#define SALEOFF 1
#define SOLDOUT 2
#define WAITING 3

class Glasses
{
public:
	char mID[10];
	char mName[50];
	char mColor[20];
	char mProducer[50];
	float mPrice;
	char mThumnail[256];
	int mStatus;
	int mTemple;
	int mEye;
	int mBridge;

	Glasses();
	~Glasses();
	void Init(char ID[] = "GLA***", char name[] = "GLASSES", char color[] = "Unknown", char producer[] = "Unknown", float price = 0.0f, char thumnail[] = NULL, int status = SOLDOUT, int temple = 0, int eye = 0, int bridge = 0);
};


#endif