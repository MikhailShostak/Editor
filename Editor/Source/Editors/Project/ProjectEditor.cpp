#include "Editors/Project/ProjectEditor.hpp"

#include ".Editor.hpp"
#include "Editors/Project/ProjectTargetType.hpp"
#include "Editors/Project/ProjectTargetDescription.hpp"
#include "Editors/Project/ProjectMultitargetDescription.hpp"
#include "Editors/Project/ProjectDescription.hpp"
#include "Data/Workspace.hpp"

namespace System
{

inline Path GetHomeDirectory()
{
    return getenv("USERPROFILE");//getenv("HOME");
}

}

System::CommandLineTool BuildTools { g_BuildToolsFolder / "Tools" };

namespace DefaultExtensions
{

inline Map<String, ProjectDescription> g_Projects;
inline System::Path currentProjectPath;
inline String currentProject;
inline String currentTarget;
inline String currentConfiguration = "Debug";
inline String currentArchitecture = "x86_64";
inline Array<String> Configurations = {
    "Debug",
    "Release",
};
inline Array<String> Architectures = {
    "x86_64",
    "x86",
};
inline Array<System::Subprocess> ActiveProcesses;

ProjectDescription *FindCurrentProject(const String &name = currentProject)
{
    for (auto &[path, project] : g_Projects)
    {
        auto p = System::Path(path).stem().generic_string();
        if (p == name)
        {
            return &project;
        }
    }
    return nullptr;
}

ProjectTargetDescription *FindTarget(const System::Path &name = currentTarget)
{
    auto project = FindCurrentProject();
    if (project)
    {
        for (auto &target : project->Targets)
        {
            if (target.Name == name)
            {
                return &target;
            }
        }
    }
    return nullptr;
}

ProjectMultitargetDescription *FindMultitarget(const System::Path &name = currentTarget)
{
    auto project = FindCurrentProject();
    if (project)
    {
        for (auto &target : project->MultitargetConfigurations)
        {
            if (target.Name == name)
            {
                return &target;
            }
        }
    }
    return nullptr;
}

System::Path GetBuildPath(const System::Path &SourcePath = currentProjectPath.parent_path())
{
    return SourcePath / ".build";
}

System::Path GetTargetBuildPath(const System::Path &SourcePath = currentProjectPath.parent_path(), const String &Configuration = currentConfiguration, const String &Architecture = currentArchitecture)
{
    return fmt::format("{}/{}-{}",
        GetBuildPath().generic_string(),
        Architecture,
        Configuration
    );
}

String GetConfigureCommand(const System::Path &SourcePath = currentProjectPath.parent_path(), const String &Configuration = currentConfiguration, const String &Architecture = currentArchitecture)
{
    System::Path compiler;
    if (Architecture == "x86_64")
    {
        compiler = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe";
    }
    else
    {
        compiler = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx86/x86/cl.exe";
    }
    System::Path cmake = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe";
    return fmt::format("{} -G Ninja -S {} -B {} -DCMAKE_C_COMPILER={} -DCMAKE_CXX_COMPILER={} -DMSVC_TOOLSET_VERSION=140 -DCMAKE_BUILD_TYPE={}",
        cmake.generic_string(),
        GetBuildPath(SourcePath).generic_string(),
        GetTargetBuildPath(SourcePath, Configuration, Architecture).generic_string(),
        compiler.generic_string(),
        compiler.generic_string(),
        Configuration
    );
}

bool GeneratePrecompiledHeader(const System::Path &Directory, const String &Name, const Array<String> &Includes)
{
    std::ofstream header;
    header.open(Directory / (Name + ".pch.hpp"), std::ios::binary);
    if (!header.is_open())
    {
        return false;
    }

    header << "#pragma once\n";
    if (!Includes.empty())
    {
        header << "\n";
        for (const auto &include : Includes)
        {
            header << fmt::format("#include <{}>\n", include);
        }
    }
    return true;
}

bool GeneratePublicHeader(const System::Path &Directory, const String &Name, const System::Path &IncludeDirectory, const Array<String> &SkipList)
{
    std::ofstream header;
    header.open(Directory / (Name + ".public.hpp"), std::ios::binary);
    if (!header.is_open())
    {
        return false;
    }

    header << "#pragma once\n";
    if (System::IsExists(IncludeDirectory))
    {
        header << "\n";
        for (const auto &entry : System::RecursiveDirectoryIterator(IncludeDirectory))
        {
            if (!entry.is_regular_file() || ArrayUtils::Contains(SkipList, entry.path().filename().generic_string()))
            {
                continue;
            }

            if (entry.path().extension() == ".h" || entry.path().extension() == ".hpp")
            {
                header << fmt::format("#include <{}>\n", System::GetRelative(entry.path(), IncludeDirectory).generic_string());
            }
        }

        header << "\n";
        for (const auto &entry : System::RecursiveDirectoryIterator(IncludeDirectory))
        {
            if (!entry.is_regular_file())
            {
                continue;
            }

            if (entry.path().extension() == ".inl")
            {
                header << fmt::format("#include <{}>\n", System::GetRelative(entry.path(), IncludeDirectory).generic_string());
            }
        }
    }

    return true;
}

bool GeneratePrivateHeader(const System::Path &Directory, const String &Name, const System::Path &IncludeDirectory, const Array<String> &SkipList)
{
    std::ofstream header;
    header.open(Directory / (Name + ".private.hpp"), std::ios::binary);
    if (!header.is_open())
    {
        return false;
    }

    header << "#pragma once\n\n";
    if (System::IsExists(IncludeDirectory))
    {
        header << "\n";
        for (const auto &entry : System::RecursiveDirectoryIterator(IncludeDirectory))
        {
            if (!entry.is_regular_file() || ArrayUtils::Contains(SkipList, entry.path().filename().generic_string()))
            {
                continue;
            }

            if (entry.path().extension() == ".h" || entry.path().extension() == ".hpp")
            {
                header << fmt::format("#include <{}>\n", System::GetRelative(entry.path(), IncludeDirectory).generic_string());
            }
        }

        header << "\n";
        for (const auto &entry : System::RecursiveDirectoryIterator(IncludeDirectory))
        {
            if (!entry.is_regular_file())
            {
                continue;
            }

            if (entry.path().extension() == ".inl")
            {
                header << fmt::format("#include <{}>\n", System::GetRelative(entry.path(), IncludeDirectory).generic_string());
            }
        }
    }
    return true;
}

bool GeneratePackageHeader(const System::Path &Directory, const String &Name)
{
    std::ofstream header;
    header.open(Directory / Name, std::ios::binary);
    if (!header.is_open())
    {
        return false;
    }
    header << "#pragma once\n";
    header << "#include <" << Name << ".pch.hpp>\n";
    header << "#include <" << Name << ".public.hpp>\n";
    return true;
}

bool GenerateProject(const System::Path &ProjectPath)
{
    auto BuildDirectory = ProjectPath.parent_path() / ".build";
    System::CreateDirectories(BuildDirectory);

    auto cmakelists = BuildDirectory / "CMakeLists.txt";
    if (!System::IsOutdated(cmakelists, ProjectPath))
    {
        return false;
    }

    ProjectDescription &project = g_Projects[ProjectPath.generic_string()];

    std::ofstream file;
    file.open(cmakelists, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }
    String projectName = ProjectPath.stem().generic_string();
    file << "cmake_minimum_required(VERSION 3.20)\n";
    file << "project(" << projectName << ")\n";
    file << R"(
if(NOT EXISTS "${CMAKE_BINARY_DIR}/Utils.cmake")
    file(DOWNLOAD "https://gist.githubusercontent.com/MikhailShostak/33c04f34492cb5cbf6c84c883cf5ebfd/raw/00f8526c5bc169770312fc8a1b3934abc40b1a0b/Utils.cmake" "${CMAKE_BINARY_DIR}/Utils.cmake")
endif()
include("${CMAKE_BINARY_DIR}/Utils.cmake")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING=1)
)";

    std::ofstream vsproject;
    vsproject.open(BuildDirectory / "CMakeSettings.json", std::ios::binary);
    if (!vsproject.is_open())
    {
        return false;
    }
    vsproject <<
        fmt::format(R"({{
  "configurations": [
    {{
      "name": "{}-x86-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "inheritEnvironments": [ "msvc_x86_x64" ],
      "buildRoot": "${{projectDir}}\\x86-Debug",
      "installRoot": "${{projectDir}}\\Binaries\\x86-Debug",
      "cmakeCommandArgs": "",
      "buildCommandArgs": "",
      "ctestCommandArgs": ""
    }},
    {{
      "name": "{}-x86-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "inheritEnvironments": [ "msvc_x86_x64" ],
      "buildRoot": "${{projectDir}}\\x86-Release",
      "installRoot": "${{projectDir}}\\Binaries\\x86-Release",
      "cmakeCommandArgs": "",
      "buildCommandArgs": "",
      "ctestCommandArgs": ""
    }},
    {{
      "name": "{}-x86_64-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "inheritEnvironments": [ "msvc_x64_x64" ],
      "buildRoot": "${{projectDir}}\\x86_64-Debug",
      "installRoot": "${{projectDir}}\\Binaries\\x86_64-Debug",
      "cmakeCommandArgs": "",
      "buildCommandArgs": "",
      "ctestCommandArgs": ""
    }},
    {{
      "name": "{}-x86_64-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "inheritEnvironments": [ "msvc_x64_x64" ],
      "buildRoot": "${{projectDir}}\\x86_64-Release",
      "installRoot": "${{projectDir}}\\Binaries\\x86_64-Release",
      "cmakeCommandArgs": "",
      "buildCommandArgs": "",
      "ctestCommandArgs": ""
    }}
  ]
}}
)", projectName, projectName, projectName, projectName);

    System::Path targetBuildDirectory = BuildDirectory / "Targets";
    System::CreateDirectories(targetBuildDirectory);

    Set<String> dependencies;
    Set<String> packages;
    for (auto &target : project.Targets)
    {
        for (const auto &dependency : target.Dependencies)
        {
            dependencies.insert(dependency);

            String package = System::Path(dependency).parent_path().generic_string();
            auto it = project.TargetPackageNames.find(package);
            if (it != project.TargetPackageNames.end())
            {
                package = it->second;
            }
            packages.insert(package);
        }
        for (const auto &dependency : target.LocalDependencies)
        {
            auto it = ranges::find_if(project.Targets, [&](const ProjectTargetDescription &target) { return target.Name.generic_string() == dependency; });
            if (it != project.Targets.end())
            {
                dependencies.insert(it->Name.stem().generic_string() + "/" + it->PackageVersion);

                String package = it->Name.stem().generic_string();
                auto it = project.TargetPackageNames.find(package);
                if (it != project.TargetPackageNames.end())
                {
                    package = it->second;
                }
                packages.insert(package);
            }
        }
    }

    if (!dependencies.empty())
    {
        file << "install_packages(\n";
        for (const auto &d : dependencies)
        {
            file << "    " << d << "\n";
        }
        file << ")\n";
    }

    for (const auto &p : packages)
    {
        file << "find_package(" << p << ")\n";
    }

    for (auto &target : project.Targets)
    {
        System::Path targetDirectory = ProjectPath.parent_path() / target.Name;
        System::Path relativeTargetDirectory = System::GetRelative(targetDirectory, BuildDirectory);
        System::Path includeDirectory = targetDirectory / "Include";
        System::Path sourceDirectory = targetDirectory / "Source";

        System::CreateDirectories(targetDirectory);

        if (target.Type != ProjectTargetType::Interface)
        {
            switch (target.Type)
            {
            case ProjectTargetType::Application:
                file << "add_application_target(" << relativeTargetDirectory.generic_string() << "\n";
                break;
            case ProjectTargetType::SharedLibrary:
                file << "add_shared_library_target(" << relativeTargetDirectory.generic_string() << "\n";
                break;
            case ProjectTargetType::StaticLibrary:
                file << "add_static_library_target(" << relativeTargetDirectory.generic_string() << "\n";
                break;
            }

            for (const auto &dependency : target.Dependencies)
            {
                String package = System::Path(dependency).parent_path().generic_string();
                auto it = project.TargetPackageNames.find(package);
                if (it != project.TargetPackageNames.end())
                {
                    package = it->second;
                }
                file << "    " << package << "\n";
            }
            for (const auto &dependency : target.LocalDependencies)
            {
                auto it = ranges::find_if(project.Targets, [&](const ProjectTargetDescription &target) { return target.Name.generic_string() == dependency; });
                if (it != project.Targets.end())
                {
                    if (!it->PackageVersion.empty())
                    {
                        file << "    " << dependency.stem().generic_string() << "\n";
                    }
                }
            }
            file << ")\n";

            if (!target.Sources.empty())
            {
                file << fmt::format("target_sources({} PRIVATE {})\n", relativeTargetDirectory.filename().generic_string(), Str::Join(target.Sources, " "));
            }
        }

        auto targetName = target.Name.stem().generic_string();

        Array<String> ExternalIncludes;
        ExternalIncludes.reserve(target.Includes.size() + target.LocalDependencies.size());
        for (const auto &include : target.Includes)
        {
            ExternalIncludes.push_back(include.generic_string());
        }
        for (const auto &include : target.LocalDependencies)
        {
            ExternalIncludes.push_back(include.stem().generic_string());
        }

        GeneratePrecompiledHeader(targetBuildDirectory, targetName, ExternalIncludes);
        GeneratePublicHeader(targetBuildDirectory, targetName, includeDirectory, target.OptionalIncludes);
        GeneratePackageHeader(targetBuildDirectory, targetName);
        GeneratePrivateHeader(targetBuildDirectory, targetName, sourceDirectory, target.OptionalIncludes);

        if (!target.PackageVersion.empty())
        {
            std::ofstream conanfile;
            conanfile.open(targetBuildDirectory / (target.Name.stem().generic_string() + ".py"), std::ios::binary);
            if (!conanfile.is_open())
            {
                return false;
            }

            String dependencies;
            for (const auto &dependency : target.Dependencies)
            {
                if (dependencies.empty())
                {
                    dependencies.append(fmt::format("{}", Str::Quote(dependency)));
                }
                else
                {
                    dependencies.append(fmt::format(", {}", Str::Quote(dependency)));
                }
            }
            for (const auto &dependency : target.LocalDependencies)
            {
                auto it = ranges::find_if(project.Targets, [&](const ProjectTargetDescription &target) { return target.Name.generic_string() == dependency; });
                if (it != project.Targets.end())
                {
                    auto localPackage = it->Name.stem().generic_string() + "/" + it->PackageVersion;
                    if (dependencies.empty())
                    {
                        dependencies.append(fmt::format("{}", Str::Quote(localPackage)));
                    }
                    else
                    {
                        dependencies.append(fmt::format(", {}", Str::Quote(localPackage)));
                    }
                }
            }
            if (!dependencies.empty())
            {
                dependencies = "requires = " + dependencies;
            }
            if (target.Type == ProjectTargetType::Interface)
            {
                conanfile << fmt::format(
R"(from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class Package(ConanFile):
    name = {}
    version = "{}"
    {}
    settings = "os", "arch", "compiler", "build_type"
    public_sources = "../../{}/Include"
    exports_sources = public_sources + "*"

    def package_info(self):
        self.cpp_info.includedirs = [".", self.public_sources]
)", target.Name.stem().generic_string(), target.PackageVersion, dependencies, target.Name.generic_string());
            }
            else
            {
                conanfile << fmt::format(
R"(from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class Package(ConanFile):
    name = {}
    version = "{}"
    {}
    settings = "os", "arch", "compiler", "build_type"
    options = {{
        "shared": [True, False],
        "fPIC" : [True, False]
    }}
    default_options = {{
        "shared": False,
        "fPIC" : True
    }}
    public_sources = "../../{}/Include"
    exports_sources = public_sources + "*"

    def generate(self):
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package_info(self):
        self.cpp_info.includedirs = [".", self.public_sources]
        self.cpp_info.libdirs = [f"../{{self.settings.arch}}-{{self.settings.build_type}}"]
        self.cpp_info.libs = [self.name]
)", target.Name.stem().generic_string(), target.PackageVersion, dependencies, target.Name.generic_string());
            }
        }
    }

    return true;
}

void ConfigureIfNeeded()
{
    GenerateProject(currentProjectPath);

    ProjectTargetDescription *target = FindTarget(currentTarget);
    if (!target || target->Type == ProjectTargetType::Interface)
    {
        return;
    }

    auto buildPath = GetTargetBuildPath();

    if (System::IsOutdated(buildPath / "CMakeCache.txt", currentProjectPath))
    {
        System::RemoveAll(buildPath);
    }

    if (!System::IsExists(buildPath))
    {
        System::CreateDirectories(buildPath);
        auto cmd = GetConfigureCommand();
        fmt::print("{}\n", cmd);
        System::RunAndWait(cmd);
    }
}

String GetBuildCommand(const System::Path &Target)
{
    System::Path cmake = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe";
    return fmt::format("{} --build {} --target {}",
        cmake.generic_string(),
        GetTargetBuildPath().generic_string(),
        System::Path(Target).stem().generic_string()
    );
}

auto BuildTargetInternally(const System::Path &Target)
{
    ProjectTargetDescription *target = FindTarget(Target);
    if (!target || target->Type == ProjectTargetType::Interface)
    {
        return 0;
    }

    auto cmd = GetBuildCommand(Target);
    fmt::print("{}\n", cmd);
    auto code = System::RunAndWait(cmd);
    if (code != 0)
    {
        fmt::print("Build failed with code: {}\n", code);
    }

    return code;
}
auto BuildCurrentTarget()
{
    ConfigureIfNeeded();
    return BuildTargetInternally(currentTarget);
}

auto BuildMultitarget(ProjectMultitargetDescription &multitarget)
{
    ConfigureIfNeeded();
    for (const auto &target : multitarget.Targets)
    {
        auto code = BuildTargetInternally(target);
        if (code != 0)
        {
            return code;
        }
    }

    return 0;
}

auto Build()
{
    auto Multitarget = FindMultitarget();
    if (Multitarget)
    {
        return BuildMultitarget(*Multitarget);
    }
    else
    {
        return BuildCurrentTarget();
    }
}

String GetRunCommand(const System::Path &Target)
{
    String executable = System::Path(Target).stem().generic_string() + ".exe";
    return (GetTargetBuildPath() / executable).generic_string();
}

void RunTargetInternally(const System::Path &Target)
{
    auto cmd = GetRunCommand(Target);
    auto exisits = System::IsRegularFile(cmd);
    cmd = Str::Quote(cmd);
    if (!exisits)
    {
        fmt::print("Executable not found: {}\n", cmd);
        return;
    }

    fmt::print("{}\n", cmd);
    ActiveProcesses.emplace_back(System::Run(cmd));
}

void RunMultitarget(ProjectMultitargetDescription &multitarget)
{
    for (const auto &target : multitarget.Targets)
    {
        RunTargetInternally(target);
    }
}

void RunCurrentTarget()
{
    RunTargetInternally(currentTarget);
}

void Run()
{
    auto Multitarget = FindMultitarget();
    if (Multitarget)
    {
        return RunMultitarget(*Multitarget);
    }
    else
    {
        return RunCurrentTarget();
    }
}

void BuildAndRun()
{
    if (Build() != 0)
    {
        return;
    }

    Run();
}

void Stop()
{
    for (auto &process : ActiveProcesses)
    {
        if (process.running())
        {
            process.terminate();
        }
    }
    ActiveProcesses.clear();
}

void GenerateHeader()
{

}

System::ConfigFile<Map<String, ProjectEditablePackage>> g_EditablePackages;

ProjectEditor::ProjectEditor()
{
    g_EditablePackages = std::move(*ProjectEditablePackageConfig.Load());
    g_EditablePackages.Path = fmt::format(fmt::runtime(g_EditablePackages.Path.generic_string()), System::GetHomeDirectory().generic_string());
    g_EditablePackages.Load();

    g_ToolBarItems["Project.EditPackage"] = []() {
        auto target = FindTarget();
        if (!target || target->PackageVersion.empty())
        {
            return;
        }

        String package = fmt::format("{}/{}", target->Name.stem().generic_string(), target->PackageVersion);
        bool editable = g_EditablePackages->find(package) != g_EditablePackages->end();
        ImGui::Text(fmt::format("{}{}", package, editable ? " (Editable)" : "").data());
        ImGui::SameLine();
        if (ImGui::Button(editable ? "Stop Edit" : "Edit"))
        {
            if (editable)
            {
                System::RunAndWait(fmt::format("conan editable remove {}", package));
            }
            else
            {
                System::Path conanfile = GetBuildPath() / "Targets" / (target->Name.stem().generic_string() + ".py");
                System::RunAndWait(fmt::format("conan editable add {} {}", conanfile.generic_string(), package));
            }
            g_EditablePackages.Load();
        }
    };
    g_ToolBarItems["Project.Selector"] = []() {
        if (currentProject.empty() && !g_Projects.empty())
        {
            auto &path = g_Projects.begin()->first;
            currentProjectPath = path;
            currentProject = currentProjectPath.stem().generic_string();
        }

        if (currentTarget.empty() && !currentProject.empty())
        {
            auto it = g_Projects.find(currentProjectPath.generic_string());
            if (it != g_Projects.end() && !it->second.Targets.empty())
            {
                currentTarget = it->second.Targets.front().Name.generic_string();
            }
        }

        ImGui::Text(!currentProject.empty() ? currentProject.data() : "Select Project");
        if (ImGui::BeginPopupContextItem("ProjectSelection", ImGuiPopupFlags_MouseButtonLeft))
        {
            for (auto &[path, project] : g_Projects)
            {
                auto p = System::Path(path).stem().generic_string();
                bool Selected = p == currentProject;
                if (ImGui::Selectable(fmt::format("{}", p).data(), &Selected))
                {
                    currentProjectPath = path;
                    currentProject = currentProjectPath.stem().generic_string();
                    currentTarget = project.Targets.front().Name.generic_string();
                }
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine();
        ImGui::Text(" > ");
        ImGui::SameLine();
        ImGui::Text(!currentTarget.empty() ? currentTarget.data() : "Select Target");
        if (ImGui::BeginPopupContextItem("TargetSelection", ImGuiPopupFlags_MouseButtonLeft))
        {
            for (auto &[path, project] : g_Projects)
            {
                auto p = System::Path(path).stem().generic_string();
                if (p != currentProject)
                {
                    continue;
                }

                for (auto &target : project.Targets)
                {
                    auto t = target.Name.generic_string();
                    bool Selected = t == currentTarget;
                    if (ImGui::Selectable(fmt::format("{}", t).data(), &Selected))
                    {
                        currentTarget = target.Name.generic_string();
                    }
                }

                for (auto &target : project.MultitargetConfigurations)
                {
                    auto t = target.Name.generic_string();
                    bool Selected = t == currentTarget;
                    if (ImGui::Selectable(fmt::format("{}", t).data(), &Selected))
                    {
                        currentTarget = target.Name.generic_string();
                    }
                }
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine();
        ImGui::Text(" > ");
        ImGui::SameLine();
        ImGui::Text(currentArchitecture.data());
        if (ImGui::BeginPopupContextItem("ArchitectureSelection", ImGuiPopupFlags_MouseButtonLeft))
        {
            for (const auto &architecture : Architectures)
            {
                auto Selected = architecture == currentArchitecture;
                if (ImGui::Selectable(architecture.data(), &Selected))
                {
                    if (Selected)
                    {
                        currentArchitecture = architecture;
                    }
                }
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine();
        ImGui::Text(" > ");
        ImGui::SameLine();
        ImGui::Text(currentConfiguration.data());
        if (ImGui::BeginPopupContextItem("ConfigurationSelection", ImGuiPopupFlags_MouseButtonLeft))
        {
            for (const auto &configuration : Configurations)
            {
                auto Selected = configuration == currentConfiguration;
                if (ImGui::Selectable(configuration.data(), &Selected))
                {
                    if (Selected)
                    {
                        currentConfiguration = configuration;
                    }
                }
            }
            ImGui::EndPopup();
        }
    };
    g_ToolBarItems["Project.TargetSelector"] = []() {
        if (currentProject.empty() && !g_Projects.empty())
        {
            auto &path = g_Projects.begin()->first;
            currentProjectPath = path;
            currentProject = currentProjectPath.stem().generic_string();
        }

        if (currentTarget.empty() && !currentProject.empty())
        {
            auto it = g_Projects.find(currentProjectPath.generic_string());
            if (it != g_Projects.end() && !it->second.Targets.empty())
            {
                currentTarget = it->second.Targets.front().Name.generic_string();
            }
        }

        String placeholder = !currentProject.empty() && !currentTarget.empty() ? fmt::format("{}/{}", currentProject, currentTarget) : String();
        ImGui::SetNextItemWidth(200);
        if (ImGui::BeginCombo("##Project.TargetSelector", placeholder.data()))
        {
            for (auto &[path, project] : g_Projects)
            {
                for (auto &target : project.Targets)
                {
                    auto p = System::Path(path).stem().generic_string();
                    auto t = target.Name.generic_string();
                    bool Selected = p == currentProject && t == currentTarget;
                    if (ImGui::Selectable(fmt::format("{}/{}", p, t).data(), &Selected))
                    {
                        currentProjectPath = path;
                        currentProject = currentProjectPath.stem().generic_string();
                        currentTarget = target.Name.generic_string();
                    }
                }
            }
            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("Current Project Target");
            ImGui::EndTooltip();
        }
    };
    g_ToolBarItems["Project.ConfigurationSelector"] = []() {
        ImGui::SetNextItemWidth(100);
        if (ImGui::BeginCombo("##Project.ConfigurationSelector", currentConfiguration.data()))
        {
            for (const auto &configuration : Configurations)
            {
                auto Selected = configuration == currentConfiguration;
                if (ImGui::Selectable(configuration.data(), &Selected))
                {
                    if (Selected)
                    {
                        currentConfiguration = configuration;
                    }
                }
            }
            ImGui::EndCombo();
        }
    };
    g_ToolBarItems["Project.ArchitectureSelector"] = []() {
        ImGui::SetNextItemWidth(100);
        if (ImGui::BeginCombo("##Project.ArchitectureSelector", currentArchitecture.data()))
        {
            for (const auto &architecture : Architectures)
            {
                auto Selected = architecture == currentArchitecture;
                if (ImGui::Selectable(architecture.data(), &Selected))
                {
                    if (Selected)
                    {
                        currentArchitecture = architecture;
                    }
                }
            }
            ImGui::EndCombo();
        }
    };

    g_ToolBarItems["Project.Clear"] = []() {
        if (ImGui::Button(ICON_MD_DELETE))
        {
            if (!currentProjectPath.empty())
            {
                System::RemoveAll(currentProjectPath.parent_path() / ".build");
            }
        }
    };
    g_ToolBarItems["Project.Build"] = []() {
        if (ImGui::Button(ICON_MD_BUILD))
        {
            Stop();

            if (currentTarget.empty())
            {
                fmt::print("Target is not selected. Please select a target.\n");
                return;
            }

            //Build();
            BuildTools.Run(
                "Build",
                "--Generator=Ninja",
                "--Linkage=Shared",
                fmt::format("--Project={}", currentProjectPath.parent_path().generic_string()),
                fmt::format("--Target={}", currentTarget),
                fmt::format("--Configuration={}", currentConfiguration)
            ).wait();
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("Build Project Target");
            ImGui::EndTooltip();
        }
    };
    g_ToolBarItems["Project.Install"] = []() {
        if (ImGui::Button(ICON_MD_INSTALL_DESKTOP))
        {
            Stop();

            if (currentTarget.empty())
            {
                fmt::print("Target is not selected. Please select a target.\n");
                return;
            }

            BuildTools.Run(
                "Package",
                "--Generator=Ninja",
                "--Linkage=Shared",
                fmt::format("--Project={}", currentProjectPath.parent_path().generic_string()),
                fmt::format("--Target={}", currentTarget),
                fmt::format("--Configuration={}", currentConfiguration)
            ).wait();
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("Install Project Target");
            ImGui::EndTooltip();
        }
    };

    g_ToolBarItems["Project.Run"] = []() {
        String icon = ActiveProcesses.empty() ? ICON_MD_PLAY_ARROW : ICON_MD_PAUSE;
        if (ImGui::Button(icon.data()))
        {
            if (ActiveProcesses.empty())
            {
                if (currentTarget.empty())
                {
                    fmt::print("Target is not selected. Please select a target.\n");
                    return;
                }

                BuildAndRun();
            }
            else
            {
                Stop();
            }
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("Run Project Target");
            ImGui::EndTooltip();
        }
    };
}

auto &FindOrAddProject(const System::Path &Path)
{
    auto [Project, New] = MapUtils::FindOrAdd(g_Projects, Path.generic_string());
    if (New)
    {
        Serialization::FromFile(Path, Project);
    }
    return Project;
}

std::optional<System::Path> FindProjectFile(const System::Path& TargetPath)
{
    System::Path currentPath = TargetPath;

    while (true)
    {
        System::Path ProjectPath = currentPath / (currentPath.filename().generic_string() + ".project");
        if (std::filesystem::exists(ProjectPath) && std::filesystem::is_regular_file(ProjectPath))
        {
            return ProjectPath;
        }

        if (currentPath.has_parent_path())
        {
            currentPath = currentPath.parent_path();
        }
        else
        {
            break;
        }
    }

    return std::nullopt;
}

void ProjectEditor::IndexFile(const System::Path &Path)
{
    if (Path.extension() != ".target")
    {
        return;
    }

    auto ProjectPath = FindProjectFile(Path.parent_path());
    auto &Project = FindOrAddProject(*ProjectPath);

    ProjectTargetDescription Target;
    Serialization::FromFile(Path, Target);
    Target.Name = Path.stem().generic_string();
    ArrayUtils::Add(Project.Targets, std::move(Target));
    //Serialization::FromFile<ProjectDescription>(Path, g_Projects[Path.generic_string()]);
}

void ProjectEditor::RenderFile(const System::Path &Path)
{
    ProjectDescription &project = g_Projects[Path.generic_string()];

    if (ImGui::Button("Make File Dirty"))
    {
        MarkFileDirty(Path);
    }

    ImGui::Text("Dependencies");
    for (auto &dependency : project.Dependencies)
    {
        ImGui::Selectable(dependency.data());
    }

    ImGui::Text("Targets");
    for (auto &target : project.Targets)
    {
        ImGui::Selectable(target.Name.generic_string().data());
    }
}

bool ProjectEditor::SaveFile(const System::Path &Source, const System::Path &Destination)
{
    GenerateProject(Destination);
    return true;
}

}
