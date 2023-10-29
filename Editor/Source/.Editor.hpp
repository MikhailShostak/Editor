#pragma once

#include "Data/Configs/ExtensionsConfig.hpp"
#include "Data/Configs/FileConfig.hpp"
#include "Data/Configs/FileBrowserConfig.hpp"
#include "Data/Configs/FileType.hpp"
#include "Data/Configs/GeneralConfig.hpp"
#include "Data/EditorConfig.hpp"
#include "Data/EditorConfigData.hpp"

#include "Editors/Project/EditablePackages/ProjectEditablePackage.hpp"
#include "Editors/Project/EditablePackages/ProjectEditablePackageConfig.hpp"
#include "Editors/Project/ProjectTargetType.hpp"
#include "Editors/Project/ProjectExecutionDescription.hpp"
#include "Editors/Project/ProjectMultitargetDescription.hpp"
#include "Editors/Project/ProjectActionDescription.hpp"
#include "Editors/Project/ProjectDependency.hpp"
#include "Editors/Project/ProjectTargetDescription.hpp"
#include "Editors/Project/ProjectDescription.hpp"
#include "Editors/Project/ProjectEditor.hpp"

#include "Subsystems/EditorSubsystem.hpp"

inline System::Path g_UserFolder = "W:/.Editor";
inline System::Path g_BuildToolsFolder = "W:/Projects/BuildTools";//g_UserFolder / "BuildTools";
inline SharedReference<System::ConfigFile<EditorConfig>> g_Config;
