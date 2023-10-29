#pragma once

struct ProjectMultitargetDescription
{
    using This = ProjectMultitargetDescription;
    System::Path Name = {};
    Array<System::Path> Targets = {};
    Array<ProjectExecutionDescription> Executions = {};

    virtual ~ProjectMultitargetDescription() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["Targets"] & Targets;
        data["Executions"] & Executions;
    }

    void Initialize()
    {
    }
};
