#pragma once

#include "Icons/IconsMaterialDesign.h"

#include "Data/Configs/ExtensionsConfig.hpp"
#include "Data/Configs/FileConfig.hpp"
#include "Data/Configs/FileBrowserConfig.hpp"
#include "Data/Configs/FileType.hpp"
#include "Data/Configs/GeneralConfig.hpp"
#include "Data/Scenes/MainWindowScene.hpp"
#include "Data/EditorConfig.hpp"
#include "Data/EditorConfigData.hpp"

#include "Editors/Project/EditablePackages/ProjectEditablePackage.hpp"
#include "Editors/Project/EditablePackages/ProjectEditablePackageConfig.hpp"
#include "Editors/Project/ProjectTargetType.hpp"
#include "Editors/Project/ProjectExecutionDescription.hpp"
#include "Editors/Project/ProjectMultitargetDescription.hpp"
#include "Editors/Project/ProjectActionDescription.hpp"
#include "Editors/Project/ProjectTargetDescription.hpp"
#include "Editors/Project/ProjectDescription.hpp"
#include "Editors/Project/ProjectEditor.hpp"

#include "Components/EditorWindow.hpp"

#include ".EditorReflection.hpp"

inline SharedReference<System::ConfigFile<EditorConfig>> g_Config;
