#include "Menu_NewUserRegister.h"
#include "../imgui/imgui_impl_dx11.h"
#include "MenuGlob.h"
#include "MenuController.h"
#define BTNBACK 111
Menu_NewUserRegister::Menu_NewUserRegister()
{
}

Menu_NewUserRegister::~Menu_NewUserRegister()
{
}

void Menu_NewUserRegister::Init()
{
	MenuBase::Init();
}
void Menu_NewUserRegister::Render(CPUTRenderParameters &renderParams)
{
	UpdateLayout(renderParams);

	DrawGUI(renderParams);
}
void Menu_NewUserRegister::HandleCPUTEvent(int eventID, int controlID, CPUTControl *control)
{
	if (eventID == CPUT_EVENT_DOWN)
	{
		switch (controlID)
		{
		case BTNBACK:
			MenuController_PopMenu(true);
			break;
		}
	}
}
void Menu_NewUserRegister::ActivationChanged(bool active)
{
	MenuBase::ActivationChanged(active);
	if (active)
	{
		CPUTGuiController *pGUI = MenuGlob_GUI();
		pGUI->CreateButton("Back", BTNBACK, MENU_CPUT_PANEL_ID);
	}
}

void Menu_NewUserRegister::DrawGUI(CPUTRenderParameters &renderParams)
{
	static User *curUser = new User();

	ImTextureID tex_id = ImGui::GetIO().Fonts->TexID;
	float tex_w = (float)ImGui::GetIO().Fonts->TexWidth;
	float tex_h = (float)ImGui::GetIO().Fonts->TexHeight;
	ImGui::Begin("Sign up");
	ImGui::Text("This is menu to add new user");
	ImGui::ImageButton(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h), 0, ImColor(0, 0, 0, 255));
	ImGui::InputText("User name", curUser->mName, 64, ImGuiInputTextFlags_CharsUppercase);
	ImGui::InputText("Email", curUser->mEmail, 255, ImGuiInputTextFlags_CharsNoBlank);
	ImGui::InputText("Address", curUser->mAddress, 255);
	ImGui::Combo("Gender", (int*) &curUser->mGender, "Male\0Female\0\0");
	ImGui::InputTextMultiline("Description", curUser->mDiscription, 255);
	
	ImGui::BlankLine(20);
	ImGui::Text("Generated User ID:");
	ImGui::BlankLine(10);
	ImGui::Text(curUser->mID);
	ImGui::BlankLine(20);
	ImGui::Button("Help", ImVec2(50, 20));
	ImGui::SameLine(ImGui::GetWindowWidth() - 150);
	ImGui::Button("Cancel", ImVec2(50, 20));
	ImGui::SameLine();
	if (ImGui::Button("OK", ImVec2(50, 20)))
	{
		
	}
	ImGui::End();
}
void Menu_NewUserRegister::UpdateLayout(CPUTRenderParameters &renderParams)
{

}