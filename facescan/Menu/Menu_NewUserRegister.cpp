#include "Menu_NewUserRegister.h"
#include "../imgui/imgui_impl_dx11.h"

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
		case 1:
			break;
		}
	}
}
void Menu_NewUserRegister::ActivationChanged(bool active)
{
	MenuBase::ActivationChanged(active);
}

void Menu_NewUserRegister::DrawGUI(CPUTRenderParameters &renderParams)
{
	char tempbuffer[256] = { 0 };
	char generatedId[] = "USER001";
	int tempint = 1;
	ImTextureID tex_id = ImGui::GetIO().Fonts->TexID;
	float tex_w = (float)ImGui::GetIO().Fonts->TexWidth;
	float tex_h = (float)ImGui::GetIO().Fonts->TexHeight;
	ImGui::Begin("Sign up");
	ImGui::Text("This is menu to add new user");
	ImGui::ImageButton(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h), 0, ImColor(0, 0, 0, 255));
	ImGui::InputText("User name", tempbuffer, 64, ImGuiInputTextFlags_CharsUppercase);
	ImGui::InputText("Email", tempbuffer, 255, ImGuiInputTextFlags_CharsNoBlank);
	ImGui::InputText("Address", tempbuffer, 255);
	ImGui::Combo("Gender", &tempint, "Male\0Female\0\0");
	ImGui::InputTextMultiline("Description", tempbuffer, 255);
	
	ImGui::BlankLine(20);
	ImGui::Text("Generated User ID:");
	ImGui::BlankLine(10);
	ImGui::Text(generatedId);
	ImGui::BlankLine(20);
	ImGui::Button("Help", ImVec2(50, 20));
	ImGui::SameLine(ImGui::GetWindowWidth() - 150);
	ImGui::Button("Cancel", ImVec2(50, 20));
	ImGui::SameLine();
	ImGui::Button("OK", ImVec2(50, 20));
	ImGui::End();
}
void Menu_NewUserRegister::UpdateLayout(CPUTRenderParameters &renderParams)
{

}