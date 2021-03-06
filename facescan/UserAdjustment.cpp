#include "UserAdjustment.h"

void UserAdjustment::readProfile(string filename)
{
	ifstream file(filename);
	string line;
	getline(file, line);
	file >> yaw
		>> pitch
		>> roll
		>> z;

	getline(file, line);
	getline(file, line);
	getline(file, line);

	file >> headWidth
		>> eyeArea
		>> cheekboneWidth
		>> occWitdh
		>> jawWidth
		>> jawLevel
		>> neckWidth;

	getline(file, line);
	getline(file, line);
	file >> oval1
		>> oval2
		>> femaleShape
		>> overallWidth
		>> roundness
		>> bmi;

	getline(file, line);
	getline(file, line);
	file >> cheekbone
		>> chinProtrude
		>> chinLevel
		>> chinWidth;

	getline(file, line);
	getline(file, line);
	file >> hairIndex;


	getline(file, line);
	getline(file, line);
	file >> mouthOpen
		>> BrowHeight;

	getline(file, line);
	getline(file, line);
	file >> skinSaturation1
		>> skinLightness1
		>> skinSaturation2
		>> skinLightness2;

	getline(file, line);
	getline(file, line);
	file >> lightHeight
		>> lightAngle
		>> directionLight
		>> ambientLight;
	file.close();
}

void UserAdjustment::writeProfile(string filename)
{
	ofstream file(filename);
	file << "#face position" << endl
		<< yaw << endl
		<< pitch << endl
		<< roll << endl
		<< z << endl;

	file << "#head shape" << endl
		<< "#7 front profile" << endl
		<< headWidth << endl
		<< eyeArea << endl
		<< cheekboneWidth << endl
		<< occWitdh << endl
		<< jawWidth << endl
		<< jawLevel << endl
		<< neckWidth << endl;

	file << "#6 base shape" << endl
		<< oval1 << endl
		<< oval2 << endl
		<< femaleShape << endl
		<< overallWidth << endl
		<< roundness << endl
		<< bmi << endl;

	file << "#4 jaw" << endl
		<< cheekbone << endl
		<< chinProtrude << endl
		<< chinLevel << endl
		<< chinWidth << endl;

	file << "#Hair" << endl
		<< hairIndex << endl;

	file << "#Head activity" << endl
		<< mouthOpen << endl
		<< BrowHeight << endl;

	file << "#Skin color" << endl
		<< skinSaturation1 << endl
		<< skinLightness1 << endl
		<< skinSaturation2 << endl
		<< skinLightness2 << endl;

	file << "#Lighting option" << endl
		<< lightHeight << endl
		<< lightAngle << endl
		<< directionLight << endl
		<< ambientLight << endl;
	file.close();
}