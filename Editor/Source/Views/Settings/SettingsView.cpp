#include "Views/Views.hpp"

namespace Settings
{

void ShowSettings(Graphics::Scene &Scene)
{
    if (DisplaySettings)
    {
        ImGui::OpenPopup("Settings");
    }

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Settings", &DisplaySettings))
    {
        static int StaticSettingsSelection = 0;
        static int ExtensionSettingsSelection = -1;
        {
            ImGui::BeginChild("Groups", ImVec2(200, 0), true);
            for (int i = 0; i < g_SettingsEntries.size(); ++i)
            {
                if (ImGui::Selectable(g_SettingsEntries[i].title.data(), StaticSettingsSelection == i))
                {
                    StaticSettingsSelection = i;
                    ExtensionSettingsSelection = -1;
                }
            }
            if (!ExtensionSettings.empty())
            {
                ImGui::Separator();
                for (int i = 0; i < ExtensionSettings.size(); ++i)
                {
                    if (ImGui::Selectable(ExtensionSettings[i].title.data(), ExtensionSettingsSelection == i))
                    {
                        StaticSettingsSelection = -1;
                        ExtensionSettingsSelection = i;
                    }
                }
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        {
            ImGui::BeginChild("Content", ImVec2(0, 0), true);
            if (StaticSettingsSelection >= 0)
            {
                g_SettingsEntries[StaticSettingsSelection].view->Draw(Scene);
            }
            else if (ExtensionSettingsSelection >= 0)
            {
                Settings::ExtensionSettings[ExtensionSettingsSelection].view->Draw(Scene);
            }
            ImGui::EndChild();
        }
        ImGui::EndPopup();
    }
}

}
