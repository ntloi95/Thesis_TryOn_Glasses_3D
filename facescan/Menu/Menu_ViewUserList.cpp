#include "Menu_ViewUserList.h"
#include "../imgui/imgui_impl_dx11.h"

Menu_ViewUserList::Menu_ViewUserList()
{
}

Menu_ViewUserList::~Menu_ViewUserList()
{
}

void Menu_ViewUserList::Init()
{

}
void Menu_ViewUserList::Render(CPUTRenderParameters &renderParams)
{
	UpdateLayout(renderParams);

	DrawGUI(renderParams);
}
void Menu_ViewUserList::HandleCPUTEvent(int eventID, int controlID, CPUTControl *control)
{

}
void Menu_ViewUserList::ActivationChanged(bool active)
{

}

void Menu_ViewUserList::DrawGUI(CPUTRenderParameters &renderParams)
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
		ImGui::Text("This is menu to search, delete, update any user");

		ImGui::PushStyleVar(ImGuiStyleVar_ChildWindowRounding, 5.0f);
		ImGui::BeginChild("Search_region", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.4f, 0), true);
		{
			ImGui::Image(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h));
			ImGui::InputText("User name", tempbuffer, 64, ImGuiInputTextFlags_CharsUppercase);
			ImGui::InputText("Email", tempbuffer, 255, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputText("Address", tempbuffer, 255);
			ImGui::Combo("Gender", &tempint, "Male\0Female\0\0");
			ImGui::InputTextMultiline("Description", tempbuffer, 255);
			ImGui::BlankLine(20);
			ImGui::InputText("User ID", tempbuffer, 255, ImGuiInputTextFlags_CharsUppercase);
			ImGui::BlankLine(20);
			ImGui::Button("Help", ImVec2(50, 20));
			ImGui::SameLine(ImGui::GetWindowWidth() - 150);
			ImGui::Button("Delete", ImVec2(50, 20));
			ImGui::SameLine();
			ImGui::Button("Update", ImVec2(50, 20));

			ImGui::EndChild();
		}

		ImGui::SameLine();
		ImGui::BeginChild("Result_region", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.6f - ImGui::GetStyle().WindowPadding.x, 0), true);
		{
			ImGui::Columns(7, "Result_Search_Table");
			ImGui::Separator();
			char ColumnNames[][20] = { "No.", "ID", "Name", "Email", "Address", "Gender", "Discript." };
			for (int i = 0; i < 7; i++)
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
				for (int j = 0; j < 6; j++)
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
void Menu_ViewUserList::UpdateLayout(CPUTRenderParameters &renderParams)
{

}