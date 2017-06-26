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

	int hairIndex;
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
