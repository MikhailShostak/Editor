#pragma once

struct ProjectDescription
{
    using This = ProjectDescription;
    Array<String> Dependencies = {};
    Array<ProjectTargetDescription> Targets = {};
    Array<ProjectMultitargetDescription> MultitargetConfigurations = {};
    Map<String, String> TargetPackageNames = {};

    virtual ~ProjectDescription() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Dependencies"] & Dependencies;
        data["Targets"] & Targets;
        data["MultitargetConfigurations"] & MultitargetConfigurations;
        data["TargetPackageNames"] & TargetPackageNames;
    }

    void Initialize()
    {
    }
};
