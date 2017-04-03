#include "Menu_Function.h"
#include "MenuController.h"
#include "CPUTGuiControllerDX11.h"
#include "MenuGlob.h"
#include "CPUTModel.h"
#include "CPUTMesh.h"
#include "CPUTTextureDX11.h"
#include "CPUTMaterial.h"
#include "../ObjLoader.h"
#include <time.h>

enum MainMenuIds
{
	MainMenuIds_Text = 0,
	MainMenuIds_Glasses,
	MainMenuIds_FaceMapping,
	MainMenuIds_FaceReview,
	MainMenuIds_TryOn
};

Menu_Function::Menu_Function()
{
}


Menu_Function::~Menu_Function()
{
}

void Menu_Function::Init()
{
	MenuBase::Init();
}

void Menu_Function::ActivationChanged(bool active)
{
	MenuBase::ActivationChanged(active);
	if (active)
	{
		CPUTGuiController *pGUI = MenuGlob_GUI();
		pGUI->CreateText("DEBUG MENU", MainMenuIds_Text, MENU_CPUT_PANEL_ID);
		pGUI->CreateButton("FACE MAPPING MODE", MainMenuIds_FaceMapping, MENU_CPUT_PANEL_ID);
		pGUI->CreateButton("GLASSES MODE", MainMenuIds_Glasses, MENU_CPUT_PANEL_ID);
		pGUI->CreateButton("VIRTUAL TRY-ON MODE", MainMenuIds_TryOn, MENU_CPUT_PANEL_ID);
	}
}

void Menu_Function::HandleCPUTEvent(int eventID, int controlID, CPUTControl *control)
{
	std::string userDir = GetUserDataDirectory();


	if (eventID == CPUT_EVENT_DOWN)
	{
		switch (controlID)
		{
		case MainMenuIds_FaceMapping:
		{
			// Push to menu Face scan or Face Preview
			std::string debugFace;
			CPUTFileSystem::CombinePath(userDir, "joe_sr300_1.obj", &debugFace);
			gMenu_FaceMapping->LoadFace(debugFace);
			MenuController_PushMenu(gMenu_FaceMapping);

		} break;
		case MainMenuIds_Glasses:
		{
			// Push to menu Glasses Preview
			std::string debugGlasses;
			CPUTFileSystem::CombinePath(userDir, "glasses.obj", &debugGlasses);
			gMenu_GlassesPreview->LoadGlassesObj(debugGlasses, true, true);
			MenuController_PushMenu(gMenu_GlassesPreview);
		} break;
		case MainMenuIds_TryOn:
		{

		}
		break;
		}
	}
}