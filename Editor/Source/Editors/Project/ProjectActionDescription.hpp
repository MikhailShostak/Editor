#pragma once

struct ProjectActionDescription
{
    using This = ProjectActionDescription;

    virtual ~ProjectActionDescription() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
