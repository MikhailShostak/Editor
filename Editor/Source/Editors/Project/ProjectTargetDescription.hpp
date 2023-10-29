#pragma once

struct PUBLIC_API_EXPORT ProjectTargetDescription
{
    using This = ProjectTargetDescription;
    System::Path Name {};
    Array<ProjectActionDescription> BuildActions {};
    Array<System::Path> LocalDependencies {};
    Array<ProjectDependency> PrivateDependencies {};
    Array<ProjectDependency> PublicDependencies {};
    Array<String> Dependencies {};
    Array<System::Path> Includes {};
    Array<String> OptionalIncludes {};
    Array<String> Sources {};
    String PackageVersion {};
    ProjectTargetType Type {};
    bool PrecompileLocalHeaders {};
    Map<String, String> PublicDefines {};
    Map<String, String> PrivateDefines {};

    virtual ~ProjectTargetDescription() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["BuildActions"] & BuildActions;
        data["LocalDependencies"] & LocalDependencies;
        data["PrivateDependencies"] & PrivateDependencies;
        data["PublicDependencies"] & PublicDependencies;
        data["Dependencies"] & Dependencies;
        data["Includes"] & Includes;
        data["OptionalIncludes"] & OptionalIncludes;
        data["Sources"] & Sources;
        data["PackageVersion"] & PackageVersion;
        data["Type"] & Type;
        data["PrecompileLocalHeaders"] & PrecompileLocalHeaders;
        data["PublicDefines"] & PublicDefines;
        data["PrivateDefines"] & PrivateDefines;
    }

    void Initialize()
    {
    }
};
