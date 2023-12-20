#include "Views/Views.hpp"
#include ".Editor.hpp"

namespace Settings
{

class FileBrowserSettingsView : public UI2::View
{
public:

void OnDraw(Graphics::Scene &Scene) override
{
    ShowFileBrowserSettings();
}

void ShowFileBrowserSettings()
{
    ImGui::Checkbox("Combine files with the same basename", &g_Config->Data.FileBrowser.CombineFilesWithSameBasename);
}

};

}
