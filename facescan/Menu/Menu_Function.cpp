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
#include "../imgui/imgui_impl_dx11.h"
#include <fstream>
#define USER_REGISTER 100
#define VIEW_LIST_USER 101
#define SCAN_NEW 102
#define SCAN_EDIT 103
#define GLASSES_REGISTER 104
#define VIEW_LIST_GLASSES 105
#define GLASSES_EDIT 106
#define GLASSES_REMOVE 107

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
	mWindowPadding = 20.0f;
	mTooltip = *new std::map<int, std::string>;
	mTooltip[USER_REGISTER] = "This function is used to register information for new user in the very fist time they use.\nAfter that, user will be scaned their face";
	mTooltip[VIEW_LIST_USER] = "This function is used to view all users in database. \nIn this view, also be able to delete, update user";
	mTooltip[SCAN_NEW] = "This function is used to scan directly \nwithout register new user for use only one time just on sever";
	mTooltip[SCAN_EDIT] = "This fuction is used to edit face mapping after scan with your user ID";
	mTooltip[GLASSES_REGISTER] = "This function is used to add new Glasses with available information";
	mTooltip[VIEW_LIST_GLASSES] = "This function is used to view all users in database.\nIn this view, also be able to delete, update glasses";
	mTooltip[GLASSES_EDIT] = "This function is used to edit a glasses with glasses ID";
	mTooltip[GLASSES_REMOVE] = "This function is used to delete a glasses with glasses ID";
	
	mNameFunction[USER_REGISTER] = "New user register";
	mNameFunction[VIEW_LIST_USER] = "View user list";
	mNameFunction[SCAN_NEW] = "Scan face user";
	mNameFunction[SCAN_EDIT] = "Edit face user";
	mNameFunction[GLASSES_REGISTER] = "Add new Glasse";
	mNameFunction[VIEW_LIST_GLASSES] = "View Glasses list";
	mNameFunction[GLASSES_EDIT] = "Edit Glasses";
	mNameFunction[GLASSES_REMOVE] = "Delete Glasses";


	freopen("recent.ini", "r", stdin);
	int function;
	for (int i = 0; i < RECENT_FUNCTION_COUNT; i++)
	{
		if (scanf("%d", &function) != EOF)
			mRecentFunction[i] = function;
		else
			mRecentFunction[i] = USER_REGISTER;
	}
	freopen("CON", "r", stdin);
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

void Menu_Function::UpdateLayout(CPUTRenderParameters &renderParams)
{
	mImGUIMenuWidth = renderParams.mWidth / 3.0f - 4*mWindowPadding;
}


void Menu_Function::DrawGUI(CPUTRenderParameters &renderParams)
{
	auto PushButton = [=](const char *s, int ID, int color, ImVec2 pos, ImVec2 size)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(color / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(color / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(color / 7.0f, 0.8f, 0.8f));
		ImGui::PushID(ID);
		ImGui::SetCursorPos(pos);
		if (ImGui::Button(s, size))
		{
			switch (ID)
			{
			case USER_REGISTER:
				MenuController_PushMenu(gMenu_NewUserRegister);
				break;
			case VIEW_LIST_USER:
				MenuController_PushMenu(gMenu_ViewUserList);
				break;
			case GLASSES_REGISTER:
				MenuController_PushMenu(gMenu_AddNewGlasses);
				break;
			case GLASSES_EDIT:
			case GLASSES_REMOVE:
			case VIEW_LIST_GLASSES:
				MenuController_PushMenu(gMenu_ViewGlassesList);
				break;
#ifndef DESIGN_UI
			case SCAN_EDIT:
			{
				std::string debugFace;
				std::string userDir = GetUserDataDirectory();
				CPUTFileSystem::CombinePath(userDir, "loi.obj", &debugFace);
				gMenu_FaceMapping->mGender = MALE;
				gMenu_FaceMapping->LoadFace(debugFace);
				MenuController_PushMenu(gMenu_FaceMapping);
			}	
				break;
#endif
#ifndef DISABLE_RSSDK
			case SCAN_NEW:
				MenuController_PushMenu(gMenu_Scan);
				break;
#endif
			}
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(mTooltip[ID].c_str());
	};

	ImGui::SetNextWindowSize(ImVec2(mImGUIMenuWidth*0.75f, renderParams.mHeight - 2*mWindowPadding));
	ImGui::SetNextWindowPos(ImVec2(mWindowPadding, mWindowPadding));
	ImGui::Begin("Most recently used function");
	float heightButton = (renderParams.mHeight - (4 + RECENT_FUNCTION_COUNT)*mWindowPadding) / RECENT_FUNCTION_COUNT;
	for (int i = 0; i < RECENT_FUNCTION_COUNT; i++)
	{
		PushButton(mNameFunction[mRecentFunction[i]].c_str(), mRecentFunction[i], i, ImVec2(mWindowPadding, i*(heightButton + mWindowPadding) + 2 * mWindowPadding), ImVec2(mImGUIMenuWidth*0.75f - 2 * mWindowPadding, heightButton));
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(mImGUIMenuWidth, renderParams.mHeight - 2*mWindowPadding));
	ImGui::SetNextWindowPos(ImVec2(mImGUIMenuWidth*0.75f + 3 * mWindowPadding, mWindowPadding));
	heightButton = (renderParams.mHeight - 8 * mWindowPadding) / 4;
	ImGui::Begin("User management tool");
	{
		PushButton(mNameFunction[USER_REGISTER].c_str(), USER_REGISTER, 1, ImVec2(mWindowPadding, 2 * mWindowPadding), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton(mNameFunction[VIEW_LIST_USER].c_str(), VIEW_LIST_USER, 2, ImVec2(mWindowPadding, 3 * mWindowPadding + heightButton), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton(mNameFunction[SCAN_NEW].c_str(), SCAN_NEW, 3, ImVec2(mWindowPadding, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
		PushButton(mNameFunction[SCAN_EDIT].c_str(), SCAN_EDIT, 4, ImVec2(0.5f*mWindowPadding + mImGUIMenuWidth/2, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(mImGUIMenuWidth, renderParams.mHeight - 2*mWindowPadding));
	ImGui::SetNextWindowPos(ImVec2(mImGUIMenuWidth*1.75f + 5 * mWindowPadding, mWindowPadding));
	ImGui::Begin("Glasses database management tool");
	{
		PushButton(mNameFunction[GLASSES_REGISTER].c_str(), GLASSES_REGISTER, 6, ImVec2(mWindowPadding, 2 * mWindowPadding), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton(mNameFunction[VIEW_LIST_GLASSES].c_str(), VIEW_LIST_GLASSES, 7, ImVec2(mWindowPadding, 3 * mWindowPadding + heightButton), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton(mNameFunction[GLASSES_REMOVE].c_str(), GLASSES_REMOVE, 5, ImVec2(mWindowPadding, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
		PushButton(mNameFunction[GLASSES_EDIT].c_str(), GLASSES_EDIT, 0, ImVec2(0.5f*mWindowPadding + mImGUIMenuWidth / 2, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
	}
	ImGui::End();
}

void Menu_Function::Render(CPUTRenderParameters &renderParams)
{
	UpdateLayout(renderParams);

	DrawGUI(renderParams);
}

CPUTEventHandledCode Menu_Function::HandleMouseEvent(int x, int y, int wheel, CPUTMouseState state, CPUTEventID message)
{
	return CPUT_EVENT_UNHANDLED;
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
#ifndef DESIGN_UI
			// Push to menu Face scan or Face Preview
			std::string debugFace;
			CPUTFileSystem::CombinePath(userDir, "loi.obj", &debugFace);
			gMenu_FaceMapping->mGender = MALE;
			gMenu_FaceMapping->LoadFace(debugFace);
			MenuController_PushMenu(gMenu_FaceMapping);
#endif
		} break;
		case MainMenuIds_Glasses:
		{
#ifndef DESIGN_UI
			// Push to menu Glasses Preview
			std::string debugGlasses;
			CPUTFileSystem::CombinePath(userDir, "glasses.obj", &debugGlasses);
			gMenu_GlassesPreview->LoadGlassesObj(debugGlasses, true, true);
			MenuController_PushMenu(gMenu_GlassesPreview);
#endif
		} break;
		case MainMenuIds_TryOn:
		{
			/*std::string debugFace, debugGlasses;
			CPUTFileSystem::CombinePath(userDir, "joe_sr300_1.obj", &debugFace);
			CPUTFileSystem::CombinePath(userDir, "glasses.obj", &debugGlasses);
			gMenu_FaceMapping->LoadFace(debugFace);
			gMenu_FaceMapping->LoadGlasses(debugGlasses);
			MenuController_PushMenu(gMenu_FaceMapping);*/
		}
		break;
		}
	}
}