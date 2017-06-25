#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct UserAdjustment
{
	float yaw;
	float pitch;
	float roll;
	float z;

	float headWidth;
	float eyeArea;
	float cheekboneWidth;
	float occWitdh;
	float jawWidth;
	float jawLevel;
	float neckWidth;

	float oval1;
	float oval2;
	float femaleShape;
	float overallWidth;
	float roundness;
	float bmi;

	float cheekbone;
	float chinProtrude;
	float chinLevel;
	float chinWidth;

	float earLevelDown;
	float earLevelUp;
	float earLobeSize;
	float earRotateForward;
	float earRotateY;
	float earSizeHorizontal;
	float earSizeVertical;
	float foreHeadHeight;
	float foreHeadSlope;
	float foreHeadWidth;

	int hairIndex;
	bool bears[5];

	float mouthOpen;
	float BrowHeight;

	int skinSaturation1;
	int skinLightness1;
	int skinSaturation2;
	int skinLightness2;

	float lightHeight;
	float lightAngle;
	float directionLight;
	float ambientLight;

	void writeProfile(string);
	void readProfile(string);
};
