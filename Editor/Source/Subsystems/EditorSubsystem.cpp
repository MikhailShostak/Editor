#include ".Editor.hpp"
#include "Subsystems/EditorSubsystem.hpp"

#include "Data/Extensions.hpp"
#include "Data/Workspace.hpp"
#include "Editors/BinaryEditor.hpp"
#include "Editors/TextEditor.hpp"

#include "Views/Views.hpp"

#include "Views/Settings/EnvironmentView.hpp"
#include "Views/Settings/ExtensionsView.hpp"
#include "Views/Settings/FileBrowserSettingsView.hpp"
#include "Views/Settings/FileTypesView.hpp"
#include "Views/Settings/GeneralSettingsView.hpp"

SharedReference<UI2::Subsystem> UISubsystem;

void LoadIcons()
{
    static ImFontConfig config;
    config.MergeMode = true;
    config.GlyphOffset = { 0, 4 };
    static const ImWchar IconsRanges[] = { ICON_MIN_MD, ICON_MAX_MD, 0 };
    UISubsystem->LoadFont("Fonts/MaterialDesignIcons/MaterialIcons-Regular.ttf", 18_px, &config, IconsRanges, [](ImFont*){});
}

void ApplyStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = { 4, 4 };
    style.FramePadding = { 4, 2 };
    style.CellPadding = { 4, 2 };
    style.ItemSpacing = { 4, 2 };
    style.ItemInnerSpacing = { 2, 2 };
    style.TouchExtraPadding = { 0, 0 };
    style.IndentSpacing = 18;
    style.ScrollbarSize = 12;
    style.GrabMinSize = 10;

    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 0;
    style.TabBorderSize = 0;

    style.WindowRounding = 4;
    style.ChildRounding = 0;
    style.FrameRounding = 2;
    style.PopupRounding = 0;
    style.ScrollbarRounding = 0;
    style.GrabRounding = 0;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 4;

    style.WindowTitleAlign = { 0.5f, 0.5f };
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = { 0.5f, 0.5f };
    style.SelectableTextAlign = { 0.0f, 0.5f };

    style.DisplaySafeAreaPadding = { 3, 3 };
}

void EditorSubsystem::CreateUI()
{
    //Super::CreateUI();
    LoadIcons();
    ApplyStyle();
}

System::CommandLineTool Conan { g_BuildToolsFolder / "Run", { "conan" } };

void EditorSubsystem::Load()
{
    Super::Load();

    UISubsystem = Core::FindSubsystem<UI2::Subsystem>();

    g_Config = &Config;

    //System::CommandLineTool git(g_UserFolder / "Git/bin/git");
    //if (!System::IsExists(g_BuildToolsFolder))
    //{
    //    git.Run("clone", "--branch", "dev", "https://github.com/MikhailShostak/BuildTools.git", g_BuildToolsFolder.generic_string()).wait();
    //    System::CommandLineTool(g_BuildToolsFolder / "Setup").Run();
    //}

    if (Config.Load())
    {
        ReloadExtensions();
        if (!g_Config->Data.File.OpenedFolders.empty())
        {
            File::DialogWorkingDirectory = g_Config->Data.File.OpenedFolders[0];
        }
    }

    g_ToolBarItems["File.New"] = []() {
        static const char* ICON_ADD_NEW = "\xee\xa2\x9c";
        if (ImGui::Button(ICON_ADD_NEW))
        {
            File::DisplayNewDialog = true;
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("New File");
            ImGui::EndTooltip();
        }
    };

    g_ToolBarItems["File.OpenFile"] = []() {
        if (ImGui::Button(ICON_MD_DESCRIPTION))
        {
            File::DisplayOpenFileDialog = true;
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("Open File");
            ImGui::EndTooltip();
        }
    };

    g_ToolBarItems["File.OpenFolder"] = []() {
        if (ImGui::Button(ICON_MD_FOLDER))
        {
            File::DisplayOpenFolderDialog = true;
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("Open Folder");
            ImGui::EndTooltip();
        }
    };

    g_ToolBarItems["File.Save"] = []() {
        if (ImGui::Button(ICON_MD_SAVE))
        {
            File::DisplaySaveAsDialog = true;
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("Save File As");
            ImGui::EndTooltip();
        }
    };

    g_RegisteredEditors.insert({ "BinaryEditor", std::make_unique<DefaultExtensions::BinaryEditor>() });
    g_RegisteredEditors.insert({ "TextEditor", std::make_unique<DefaultExtensions::TextEditor>() });
    g_RegisteredEditors.insert({ "ProjectEditor", std::make_unique<DefaultExtensions::ProjectEditor>() });

    g_RegisteredWindows.insert({ "PackageWindow", std::make_shared<PackageManagerView>() });

    ArrayUtils::Add(g_SettingsEntries, {
        { "General", CreateShared<Settings::GeneralSettingsView>() },
        { "FileBrowser", CreateShared<Settings::FileBrowserSettingsView>() },
        { "Environment", CreateShared<Settings::EnvironmentView>() },
        { "Extensions", CreateShared<Settings::ExtensionsView>() },
        { "File Types", CreateShared<Settings::FileTypesView>() },
    });

    //ClassGen::LoadExtensions();
    //g_ExtensionLibrary.Navigate = [](const ClassGen::FileInfo& type)
    //{
    //    if (System::IsRegularFile(type.Path))
    //    {
    //        OpenFile(type.Path, false);
    //    }
    //};

    ReloadFiles();
}

void EditorSubsystem::Unload()
{
    Config.Save();

    Super::Unload();
}

void EditorSubsystem::RenderScene(Graphics::Window & Window, Graphics::Scene & Scene)
{
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        CreateUI();
    }
    
    /*for (auto &[id, request] : g_DrawRequests)
    {
        request(GraphicsContext);
    }*/
}
