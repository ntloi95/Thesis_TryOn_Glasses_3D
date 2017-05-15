#include "Menu_AddNewGlasses.h"
#include "../imgui/imgui_impl_dx11.h"

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

}
void Menu_AddNewGlasses::ActivationChanged(bool active)
{

}

void Menu_AddNewGlasses::DrawGUI(CPUTRenderParameters &renderParams)
{
	static bool openWindows = 0;
	char tempbuffer[256] = { 0 };
	int tempint = 1;
	float tempfloat = 0.1f;
	ImTextureID tex_id = ImGui::GetIO().Fonts->TexID;
	float tex_w = (float)ImGui::GetIO().Fonts->TexWidth;
	float tex_h = (float)ImGui::GetIO().Fonts->TexHeight;
	ImGui::Begin("Add new glasses", &openWindows);
	ImGui::Text("This is menu to add new glasses");
	ImGui::Image(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h));

	ImGui::InputText("Generated Glasses ID", tempbuffer, 64, ImGuiInputTextFlags_CharsUppercase);
	ImGui::InputText("Glasses name", tempbuffer, 64, ImGuiInputTextFlags_CharsUppercase);
	ImGui::Combo("Color", &tempint, "Black\0White\0Gold\0Silver\0Other...\0\0");
	ImGui::Combo("Producer", &tempint, "Rayban\0Oakley\0Chanel\0Prada\0Other...\0\0");
	ImGui::InputFloat("Price", &tempfloat);
	ImGui::Combo("Status", &tempint, "Available\0Sale off\0Sold out\0\0");
	ImGui::BlankLine(20);

	ImGui::Text("Size of Glasses:");
	ImGui::TagColumn(20);
	ImGui::InputInt("Temple", &tempint);
	ImGui::TagColumn(20);
	ImGui::InputInt("Eyes", &tempint);
	ImGui::TagColumn(20);
	ImGui::InputInt("Bridge", &tempint);
	ImGui::BlankLine(20);

	ImGui::Text("Thumnail link: %s", tempbuffer);
	ImGui::SameLine(ImGui::GetWindowWidth() - 150);
	ImGui::Button("Open...");
	ImGui::BlankLine(20);

	ImGui::Button("Help", ImVec2(50, 20));
	ImGui::SameLine(ImGui::GetWindowWidth() - 150);
	ImGui::Button("Cancel", ImVec2(50, 20));
	ImGui::SameLine();
	ImGui::Button("OK", ImVec2(50, 20));
	ImGui::End();
}
void Menu_AddNewGlasses::UpdateLayout(CPUTRenderParameters &renderParams)
{

}