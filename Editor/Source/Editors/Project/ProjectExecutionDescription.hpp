#pragma once

struct ProjectExecutionDescription
{
    using This = ProjectExecutionDescription;
    System::Path Application = {};
    Array<String> Arguments = {};

    virtual ~ProjectExecutionDescription() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Application"] & Application;
        data["Arguments"] & Arguments;
    }

    void Initialize()
    {
    }
};
