
#include "Views/View/MainWindowView.hpp"

#include "Data/Workspace.hpp"
#include "Views/Views.hpp"

#include ".Editor.hpp"

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

            auto it2 = std::find_if(g_RegisteredEditors.begin(), g_RegisteredEditors.end(), [&](const auto& v)
            {
                return v.first == EditorName;
            });
            if (it2 == g_RegisteredEditors.end())
            {
                continue;
            }

            const std::unique_ptr<EditorAPI::Editor>& editor = it2->second;
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

void MainWindowView::Draw(Graphics::Scene & Scene)
{
    auto UISubsystem = Core::FindSubsystem<UI2::Subsystem>();
    /*g_GraphicsContext = &GraphicsContext;
    g_SceneWindow = this;*/

    UISubsystem = Core::FindSubsystem<UI2::Subsystem>();
    UISubsystem->PushUIFont();
    ShowRootView(&OnToolBarUpdate, &OnContentUpdate);

    File::ProcessDialogs();
    Super::Draw(Scene);
    for (auto &[Title, View] : g_RegisteredWindows)
    {
        View->Draw(Scene);
        /*if (ImGui::Begin(Title.data()))
        {
        }
        ImGui::End();*/
    }
    Settings::ShowSettings(Scene);
    ::View::ShowFileBrowser();
    ::View::ShowConsole();
    Tools::ShowImportWindow();
    if (Debug::DisplayImGuiDemo)
    {
        ImGui::ShowDemoWindow();
    }
    Debug::ShowDebugWindow();
    UISubsystem->PopFont();
    //g_GraphicsContext = nullptr;
}
