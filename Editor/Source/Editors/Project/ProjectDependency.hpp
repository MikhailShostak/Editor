#pragma once

struct PUBLIC_API_EXPORT ProjectDependency
{
    using This = ProjectDependency;
    System::Path Name {};

    virtual ~ProjectDependency() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
    }

    void Initialize()
    {
    }
};
