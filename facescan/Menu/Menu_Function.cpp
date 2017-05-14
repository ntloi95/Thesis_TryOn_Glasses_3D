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

void PushButton(char *s, int ID, int color, ImVec2 pos, ImVec2 size)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(color / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(color / 7.0f, 0.7f, 0.7f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(color / 7.0f, 0.8f, 0.8f));
	ImGui::PushID(ID);
	ImGui::SetCursorPos(pos);
	ImGui::Button(s, size);
	ImGui::PopStyleColor(3);
	ImGui::PopID();
}
void Menu_Function::DrawGUI(CPUTRenderParameters &renderParams)
{
	ImGui::SetNextWindowSize(ImVec2(mImGUIMenuWidth*0.75f, renderParams.mHeight - 2*mWindowPadding));
	ImGui::SetNextWindowPos(ImVec2(mWindowPadding, mWindowPadding));
	ImGui::Begin("Most recently used function");
	float heightButton = (renderParams.mHeight - (4 + RECENT_FUNCTION_COUNT)*mWindowPadding) / RECENT_FUNCTION_COUNT;
	for (int i = 0; i < RECENT_FUNCTION_COUNT; i++)
	{
		ImGui::PushID(i);
		ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
		
		ImGui::SetCursorPos(ImVec2(mWindowPadding, i*(heightButton+mWindowPadding) + 2*mWindowPadding));
		char buttonName[256];
		sprintf(buttonName, "Recently function %d", i);
		ImGui::Button(buttonName, ImVec2(mImGUIMenuWidth*0.75f - 2 * mWindowPadding, heightButton));
		ImGui::PopStyleColor(3);
		ImGui::PopID();
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(mImGUIMenuWidth, renderParams.mHeight - 2*mWindowPadding));
	ImGui::SetNextWindowPos(ImVec2(mImGUIMenuWidth*0.75f + 3 * mWindowPadding, mWindowPadding));
	heightButton = (renderParams.mHeight - 8 * mWindowPadding) / 4;
	ImGui::Begin("User management tool");
	{
		PushButton("New user register", USER_REGISTER, 1, ImVec2(mWindowPadding, 2 * mWindowPadding), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton("View user list", VIEW_LIST_USER, 2, ImVec2(mWindowPadding, 3 * mWindowPadding + heightButton), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton("Scan face user", SCAN_NEW, 3, ImVec2(mWindowPadding, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
		PushButton("Edit face user", SCAN_EDIT, 4, ImVec2(0.5f*mWindowPadding + mImGUIMenuWidth/2, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(mImGUIMenuWidth, renderParams.mHeight - 2*mWindowPadding));
	ImGui::SetNextWindowPos(ImVec2(mImGUIMenuWidth*1.75f + 5 * mWindowPadding, mWindowPadding));
	ImGui::Begin("Glasses database management tool");
	{
		PushButton("Add new glasses ", GLASSES_REGISTER, 6, ImVec2(mWindowPadding, 2 * mWindowPadding), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton("View glasses list", VIEW_LIST_GLASSES, 7, ImVec2(mWindowPadding, 3 * mWindowPadding + heightButton), ImVec2(mImGUIMenuWidth - 2 * mWindowPadding, heightButton));
		PushButton("Delete glasses", GLASSES_REMOVE, 5, ImVec2(mWindowPadding, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
		PushButton("Edit glasses", SCAN_EDIT, 0, ImVec2(0.5f*mWindowPadding + mImGUIMenuWidth / 2, 4 * mWindowPadding + 2 * heightButton), ImVec2(mImGUIMenuWidth / 2 - 1.5f*mWindowPadding, 2 * heightButton + mWindowPadding));
	}
	ImGui::End();
}

void Menu_Function::Render(CPUTRenderParameters &renderParams)
{
	UpdateLayout(renderParams);

	DrawGUI(renderParams);
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