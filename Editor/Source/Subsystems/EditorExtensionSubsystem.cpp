#include <EditorAPI.hpp>
#include "Views/Views.hpp"
#include "Subsystems/EditorExtensionSubsystem.hpp"
#include "Subsystems/Conan/ConanPackage.hpp"

#include "Editors/Editor.hpp"

#include "Data/Workspace.hpp"

using ConanPackageList = Map<String, ConanPackage>;

Conan conan;
String ConanVersion;
Map<String, System::Path> DevPackages;
ConanPackageList InstalledPackages;
ConanPackageList RemotePackages;
String ConanPackageFilter = "*";

Map<String, ClassReference<EditorAPI::EditorFileEditor>> g_EditorFileEditorClasses;
Map<String, ClassReference<EditorAPI::EditorSettings>> g_EditorSettingsClasses;

void ReloadInstalledPackages()
{
    Map<String, Map<String, String>> EditablePackages = conan.GetEditablePackages();
    for (auto &[PackageID, Package] : EditablePackages)
    {
        if (boost::starts_with(PackageID, "editor."))
        {
            DevPackages[PackageID] = System::Path(Package["path"]).parent_path();
        }
    }
    InstalledPackages = conan.GetData<Map<String, ConanPackageList>>("list", "editor.*")["Local Cache"];
}

void EditorExtensionSubsystem::Load()
{
    Super::Load();
    
    ConanVersion = conan.GetOutput("-v");
    ReloadInstalledPackages();

    for (auto &[PackageID, Path] : DevPackages)
    {
        fmt::print("{}: {}", PackageID, Path.generic_string());
        auto PackageFolder = Path / "Debug";
        if (!System::IsExists(PackageFolder))
        {
            continue;
        }
        
        Extensions.Load(PackageFolder);
    }

    for (auto &Extension : Extensions.Extensions)
    {
        Extension->OnLoad(this);
    }
}

void EditorExtensionSubsystem::Unload()
{
    for (auto &Extension : Extensions.Extensions)
    {
        Extension->OnUnload();
    }

    Super::Unload();
}

void EditorExtensionSubsystem::ShowExtensions()
{
    ImGui::Text(ConanVersion.data());

    ImGui::InputText("Search Package", &ConanPackageFilter);
    ImGui::SameLine();
    if (ImGui::Button("Search"))
    {
        RemotePackages = conan.GetData<Map<String, ConanPackageList>>("list", "-r", "Artifactory", "editor." + ConanPackageFilter)["Artifactory"];
    }

    Array<String> PackagesToRemove;

    for (auto &[PackageID, Package] : DevPackages)
    {
        ImGui::Text(PackageID.data());
        ImGui::SameLine();
        if (ImGui::Button("Disable"))
        {
            PackagesToRemove.push_back(PackageID);
        }
    }

    for (auto &[PackageID, Package] : InstalledPackages)
    {
        ImGui::Text(PackageID.data());
        ImGui::SameLine();
        if (ImGui::Button("Uninstall"))
        {
            PackagesToRemove.push_back(PackageID);
        }
    }

    if (!PackagesToRemove.empty())
    {
        for (auto &PackageID : PackagesToRemove)
        {
            conan.Run("remove", "-c", PackageID).wait();
        }
        ReloadInstalledPackages();
    }
    
    for (auto &[PackageID, Package] : RemotePackages)
    {
        if (InstalledPackages.contains(PackageID))
        {
            continue;
        }

        ImGui::Text(PackageID.data());
        ImGui::SameLine();
        if (ImGui::Button("Install"))
        {
            conan.Run("download", "-r", "Artifactory", PackageID).wait();
            ReloadInstalledPackages();
        }
    }
}

void EditorExtensionSubsystem::RegisterFileEditor(const String & Title, const ClassReference<EditorAPI::Editor> & Editor)
{
    g_RegisteredEditors.insert({ Title, Editor->Create() });
}

void EditorExtensionSubsystem::RegisterSettings(const String & Title, const ClassReference<UI2::View> & Settings)
{
    g_SettingsEntries.push_back({ Title, Settings->CreateShared() });
}

#include "Views/Views.hpp"

void EditorExtensionSubsystem::RegisterWindow(const String & Title, const ClassReference<UI2::View> & View)
{
    g_RegisteredWindows.insert({ Title, SharedReference<UI2::View>(View->Create().release()) });
}

void EditorExtensionSubsystem::MarkFileDirty(const System::Path &Path, const EditorAPI::Editor &Editor)
{
    //TODO: wtf?
    //auto it = std::find_if(g_RegisteredEditors.begin(), g_RegisteredEditors.end(), [&](const auto &v){ return v.second.get() == &Editor; });
    UnsavedFiles[Path.generic_string()] = ConstCast(&Editor);//it->second.get();
}
