#include ".Editor.hpp"
#include "Subsystems/EditorSubsystem.hpp"

#include "Data/Extensions.hpp"
#include "Data/Workspace.hpp"
#include "Editors/BinaryEditor.hpp"
#include "Editors/ClassGenEditor.hpp"
#include "Editors/TextEditor.hpp"
#include "Views/Views.hpp"


#include <Class.gen.hpp>

SharedReference<UI2::Subsystem> UISubsystem;

void OnToolBarUpdate()
{
    for (const auto &item : g_ActiveToolBarItems)
    {
        auto it = g_ToolBarItems.find(item);
        if (it != g_ToolBarItems.end())
        {
            ImGui::SameLine();
            it->second();
        }
    }
}

void OnContentUpdate()
{
    ImGuiID Workspace = ImGui::GetID("Workspace");

    std::vector<std::filesystem::path> FilesToClose;
    for (const auto& f : g_Config->Data.File.OpenedFiles)
    {
        ImGui::SetNextWindowDockID(Workspace, ImGuiCond_Once);
        bool IsOpen = true;
        if (ImGui::Begin(GetFileTitle(f).data(), &IsOpen))
        {
            //ImGuiContext& g = *GImGui;
            //if (ImGui::IsMouseReleased(1) && (g.CurrentWindow->ID == g.HoveredId || ImGui::IsItemHovered()))
            //{
            //    ImGui::OpenPopup("FileContextMenu");
            //}
            if (ImGui::BeginPopup("FileContextMenu"))
            {
                //auto directory = is_directory ? path : path.parent_path();
                if (ImGui::MenuItem("Save"))
                {
                    SaveFile(f);
                }
                if (ImGui::MenuItem("Save As..."))
                {
                    File::DisplaySaveAsDialog = true;
                    File::FileToSave = f;
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Close"))
                {
                    FilesToClose.push_back(f);
                }
                ImGui::Separator();
                Utils::Menu::ShowDefaultFileOperations(f);
                ImGui::EndPopup();
            }

            std::string ext = f.extension().string();
            std::string EditorName = "TextEditor";
            auto it1 = ranges::find_if(g_Config->Data.FileTypes, [&](const auto& v)
            {
                return v.Extensions == ext;
            });
            if (it1 != g_Config->Data.FileTypes.end())
            {
                EditorName = it1->Editor;
            }

            auto it2 = std::find_if(Editors.begin(), Editors.end(), [&](const auto& v)
            {
                return v.first == EditorName;
            });
            if (it2 == Editors.end())
            {
                continue;
            }

            const std::unique_ptr<Editor>& editor = it2->second;
            editor->RenderFile(f);
        }

        if (!IsOpen)
        {
            FilesToClose.push_back(f);
        }

        ImGui::End();
    }
    if (!FilesToClose.empty())
    {
        CloseFiles(FilesToClose);
    }
    if (PendingReindex)
    {
        ReindexFiles();
    }
}

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

    g_Config = Config;

    //System::CommandLineTool git(g_UserFolder / "Git/bin/git");
    //if (!System::IsExists(g_BuildToolsFolder))
    //{
    //    git.Run("clone", "--branch", "dev", "https://github.com/MikhailShostak/BuildTools.git", g_BuildToolsFolder.generic_string()).wait();
    //    System::CommandLineTool(g_BuildToolsFolder / "Setup").Run();
    //}

    if (Config->Load())
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

    Editors.insert({ "BinaryEditor", std::make_unique<DefaultExtensions::BinaryEditor>() });
    Editors.insert({ "TextEditor", std::make_unique<DefaultExtensions::TextEditor>() });
    //Editors.insert({ "ClassGenEditor", std::make_unique<DefaultExtensions::ClassGenEditor>() });
    Editors.insert({ "ProjectEditor", std::make_unique<DefaultExtensions::ProjectEditor>() });

    ClassGen::LoadExtensions();
    g_ExtensionLibrary.Navigate = [](const ClassGen::FileInfo& type)
    {
        if (System::IsRegularFile(type.Path))
        {
            OpenFile(type.Path, false);
        }
    };

    ReloadFiles();
}

void EditorSubsystem::Unload()
{
    Config->Save();

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
    }


    g_GraphicsContext = &GraphicsContext;
    g_SceneWindow = this;*/

    UISubsystem->PushUIFont();
    ShowRootView(&OnToolBarUpdate, &OnContentUpdate);

    File::ProcessDialogs();

    Settings::ShowSettings();
    View::ShowFileBrowser();
    View::ShowConsole();
    Tools::ShowImportWindow();
    if (Debug::DisplayImGuiDemo)
    {
        ImGui::ShowDemoWindow();
    }
    Debug::ShowDebugWindow();
    UISubsystem->PopFont();
    //g_GraphicsContext = nullptr;
}
