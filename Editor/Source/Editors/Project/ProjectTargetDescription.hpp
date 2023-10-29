#pragma once

struct ProjectTargetDescription
{
    using This = ProjectTargetDescription;
    System::Path Name = {};
    Array<ProjectActionDescription> BuildActions = {};
    Array<System::Path> LocalDependencies = {};
    Array<String> Dependencies = {};
    Array<System::Path> Includes = {};
    Array<String> OptionalIncludes = {};
    Array<String> Sources = {};
    String PackageVersion = {};
    ProjectTargetType Type = {};

    virtual ~ProjectTargetDescription() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["BuildActions"] & BuildActions;
        data["LocalDependencies"] & LocalDependencies;
        data["Dependencies"] & Dependencies;
        data["Includes"] & Includes;
        data["OptionalIncludes"] & OptionalIncludes;
        data["Sources"] & Sources;
        data["PackageVersion"] & PackageVersion;
        data["Type"] & Type;
    }

    void Initialize()
    {
    }
};
