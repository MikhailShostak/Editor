#include "Views/Views.hpp"
#include ".Editor.hpp"

namespace Settings
{

void ShowFileBrowserSettings()
{
    ImGui::Checkbox("Combine files with the same basename", &g_Config->Data.FileBrowser.CombineFilesWithSameBasename);
}

}
