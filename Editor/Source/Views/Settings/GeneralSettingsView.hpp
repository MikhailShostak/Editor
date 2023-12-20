#include "Views/Views.hpp"
#include ".Editor.hpp"

namespace Settings
{

class GeneralSettingsView : public UI2::View
{
public:

void OnDraw(Graphics::Scene &Scene) override
{
    ShowGeneralSettings();
}

void ShowGeneralSettings()
{
    std::string externalTextEditor = g_Config->Data.General.ExternalTextEditor;
    if (ImGui::InputText("External Text Editor", &externalTextEditor, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        g_Config->Data.General.ExternalTextEditor = externalTextEditor;
    }
}

};

}
