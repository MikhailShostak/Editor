#pragma once

inline Map<String, SharedReference<UI2::View>> g_RegisteredWindows;

struct SettingsEntry
{
    String title;
    SharedReference<UI2::View> view;
};

inline Array<SettingsEntry> g_SettingsEntries;

void ShowRootView(const std::function<void()>& ToolBar, const std::function<void()>& Content);
void ShowMainMenu();
void ShowWelcomePage();

namespace File
{
inline bool DisplayNewDialog = false;
inline bool DisplayOpenFileDialog = false;
inline bool DisplayOpenFolderDialog = false;
inline bool DisplaySaveAsDialog = false;
inline std::filesystem::path DialogWorkingDirectory = ".";
inline std::filesystem::path FileToSave;
void ShowNewDialog();
void ShowOpenFileDialog();
void ShowOpenFolderDialog();
void ShowSaveAsDialog();
void ProcessDialogs();
}

namespace Settings
{

inline bool DisplaySettings = false;
void ShowSettings(Graphics::Scene &Scene);

inline std::vector<SettingsEntry> ExtensionSettings;

}

namespace View
{

inline bool DisplayConsole = false;
void ShowConsole();

inline bool DisplayFileBrowser = true;
void ShowFileBrowser();


}

namespace Tools
{

inline bool DisplayImportWindow = false;
void ShowImportWindow();

}

namespace Utils
{

namespace Menu
{
void CopyFullPath(const std::filesystem::path &path);
void ShowInExplorer(const std::filesystem::path &path);
void ShowInExternalTextEditor(const std::filesystem::path &path);
void OpenTerminalHere(const std::filesystem::path &path);
void ShowDefaultFileOperations(const std::filesystem::path &path);
}

}

namespace Debug
{

inline bool DisplayImGuiDemo = false;
inline bool DisplayDebugWindow = false;

void ShowDebugWindow();

}

inline static ImGuiTableFlags DefaultTableFlags =
    ImGuiTableFlags_SizingFixedFit |
    ImGuiTableFlags_RowBg |
    ImGuiTableFlags_Borders |
    ImGuiTableFlags_Resizable |
    ImGuiTableFlags_Hideable;
