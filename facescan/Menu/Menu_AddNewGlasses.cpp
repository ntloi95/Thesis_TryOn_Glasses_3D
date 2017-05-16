#include "Menu_AddNewGlasses.h"
#include "../imgui/imgui_impl_dx11.h"
#include "MenuGlob.h"
#include "MenuController.h"
#define BTNBACK 111
#define BTNOPEN 200
#define BTNHELP 201
#define BTNCANCEL 202
#define BTNOK 203
const char HELPTOOLTIP[] = "Try to fill all of text box\nprogram will generate randomly a distinct id for glasses\You also can set a id for glasses but must handle it's unique";
const char GLASSESCOLOR[][20] = { "Black", "White", "Gold", "Silver", "Other..." };
const char PRODUCER[][20] = { "Rayban", "Oakley", "Chanel", "Prada", "Other..." };

Menu_AddNewGlasses::Menu_AddNewGlasses()
{
}

Menu_AddNewGlasses::~Menu_AddNewGlasses()
{
}

void Menu_AddNewGlasses::Init()
{

}
void Menu_AddNewGlasses::Render(CPUTRenderParameters &renderParams)
{
	UpdateLayout(renderParams);

	DrawGUI(renderParams);
}
void Menu_AddNewGlasses::HandleCPUTEvent(int eventID, int controlID, CPUTControl *control)
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
void Menu_AddNewGlasses::ActivationChanged(bool active)
{
	MenuBase::ActivationChanged(active);
	if (active)
	{
		CPUTGuiController *pGUI = MenuGlob_GUI();
		pGUI->CreateButton("Back", BTNBACK, MENU_CPUT_PANEL_ID);
	}
}

void Menu_AddNewGlasses::DrawGUI(CPUTRenderParameters &renderParams)
{
	static bool openWindows = 0;
	static Glasses *curGlasses = new Glasses();
	static int colorIndex;
	static int producerIndex;

	ImTextureID tex_id = ImGui::GetIO().Fonts->TexID;
	float tex_w = (float)ImGui::GetIO().Fonts->TexWidth;
	float tex_h = (float)ImGui::GetIO().Fonts->TexHeight;
	ImGui::Begin("Add new glasses", &openWindows);
	ImGui::Text("This is menu to add new glasses");
	ImGui::Image(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h));

	ImGui::InputText("Generated Glasses ID", curGlasses->mID, 64, ImGuiInputTextFlags_CharsUppercase);
	ImGui::InputText("Glasses name", curGlasses->mName, 64, ImGuiInputTextFlags_CharsUppercase);
	ImGui::Combo("Color", &colorIndex, "Black\0White\0Gold\0Silver\0Other...\0\0");
	ImGui::Combo("Producer", &producerIndex, "Rayban\0Oakley\0Chanel\0Prada\0Other...\0\0");
	ImGui::InputFloat("Price", &curGlasses->mPrice);
	ImGui::Combo("Status", &curGlasses->mStatus, "Available\0Sale off\0Sold out\0\0");
	ImGui::BlankLine(20);

	ImGui::Text("Size of Glasses:");
	ImGui::TagColumn(20);
	ImGui::InputInt("Temple", &curGlasses->mTemple);
	ImGui::TagColumn(20);
	ImGui::InputInt("Eyes", &curGlasses->mEye);
	ImGui::TagColumn(20);
	ImGui::InputInt("Bridge", &curGlasses->mBridge);
	ImGui::BlankLine(20);

	ImGui::Text("Thumnail link: %s", curGlasses->mThumnail);
	ImGui::SameLine(ImGui::GetWindowWidth() - 150);
	ImGui::PushID(BTNOPEN);
	if (ImGui::Button("Open..."))
	{
		OPENFILENAMEA ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = curGlasses->mThumnail;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(curGlasses->mThumnail);
		ofn.lpstrFilter = "PNG\0*.png\0JPG\0*.jpg\0All file\0*.*\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		GetOpenFileNameA(&ofn);
	}
	ImGui::PopID();
	ImGui::BlankLine(20);

	ImGui::PushID(BTNHELP);
	ImGui::Button("Help", ImVec2(50, 20));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(HELPTOOLTIP);
	ImGui::PopID();
	ImGui::SameLine(ImGui::GetWindowWidth() - 150);
	ImGui::PushID(BTNCANCEL);
	ImGui::Button("Cancel", ImVec2(50, 20));
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(BTNOK);
	if (ImGui::Button("OK", ImVec2(50, 20)))
	{
		strcpy(curGlasses->mColor, GLASSESCOLOR[colorIndex]);
		strcpy(curGlasses->mProducer, PRODUCER[producerIndex]);
	}
	ImGui::PopID();
	ImGui::End();
}
void Menu_AddNewGlasses::UpdateLayout(CPUTRenderParameters &renderParams)
{

}