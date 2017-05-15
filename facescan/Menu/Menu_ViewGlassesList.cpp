#include "Menu_ViewGlassesList.h"
#include "../imgui/imgui_impl_dx11.h"

Menu_ViewGlassesList::Menu_ViewGlassesList()
{
}

Menu_ViewGlassesList::~Menu_ViewGlassesList()
{
}

void Menu_ViewGlassesList::Init()
{

}
void Menu_ViewGlassesList::Render(CPUTRenderParameters &renderParams)
{
	UpdateLayout(renderParams);

	DrawGUI(renderParams);
}
void Menu_ViewGlassesList::HandleCPUTEvent(int eventID, int controlID, CPUTControl *control)
{

}
void Menu_ViewGlassesList::ActivationChanged(bool active)
{

}

void Menu_ViewGlassesList::DrawGUI(CPUTRenderParameters &renderParams)
{
	static bool open = 1;
	char tempbuffer[256] = { 0 };
	int tempint = 1;
	float tempfloat = 0.1f;
	ImTextureID tex_id = ImGui::GetIO().Fonts->TexID;
	float tex_w = (float)ImGui::GetIO().Fonts->TexWidth;
	float tex_h = (float)ImGui::GetIO().Fonts->TexHeight;
	ImGui::Begin("View list Glasses", &open);
	{
		ImGui::Text("This is menu to search, delete, update any Glasses");

		ImGui::PushStyleVar(ImGuiStyleVar_ChildWindowRounding, 5.0f);
		ImGui::BeginChild("Search_region", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.3f, 0), true);
		{
			ImGui::Image(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h));

			ImGui::InputText("Glasses ID", tempbuffer, 64, ImGuiInputTextFlags_CharsUppercase);
			ImGui::InputText("Glasses name", tempbuffer, 64, ImGuiInputTextFlags_CharsUppercase);
			ImGui::Combo("Color", &tempint, "Black\0White\0Gold\0Silver\0Other...\0\0");
			ImGui::Combo("Producer", &tempint, "Rayban\0Oakley\0Chanel\0Prada\0Other\0\0");
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
			ImGui::Button("Delete", ImVec2(50, 20));
			ImGui::SameLine();
			ImGui::Button("Update", ImVec2(50, 20));
			ImGui::EndChild();
		}

		ImGui::SameLine();
		ImGui::BeginChild("Result_region", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.7f - ImGui::GetStyle().WindowPadding.x, 0), true);
		{
			ImGui::Columns(11, "Result_Search_Table");
			ImGui::Separator();
			char ColumnNames[][11] = { "No.", "ID", "Name", "Color", "Producer", "Price", "Thumnail", "Status", "Temple", "Eye", "Bridge" };
			for (int i = 0; i < 11; i++)
			{
				ImGui::Text(ColumnNames[i]);
				ImGui::NextColumn();
			}
			ImGui::Separator();
			static int selected = -1;
			for (int i = 0; i < 100; i++)
			{
				char label[32];
				sprintf(label, "%04d", i);
				if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
					selected = i;
				ImGui::NextColumn();
				for (int j = 0; j < 10; j++)
				{
					ImGui::Text("NULL");
					ImGui::NextColumn();
				}
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}

		ImGui::PopStyleVar();



		ImGui::End();
	}
}
void Menu_ViewGlassesList::UpdateLayout(CPUTRenderParameters &renderParams)
{

}