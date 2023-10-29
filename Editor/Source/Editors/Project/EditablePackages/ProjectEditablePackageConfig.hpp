#pragma once

inline DynamicAsset<System::ConfigFile<Map<String, ProjectEditablePackage>>> ProjectEditablePackageConfig = { "ProjectEditablePackageConfig", [](auto &instance)
{
Serialization::FromString(R"(
Path: "{}/.conan/editable_packages.json"
)",
instance);
} };
