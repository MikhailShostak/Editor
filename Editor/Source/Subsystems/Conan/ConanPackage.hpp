#pragma once

struct PUBLIC_API_EXPORT ConanPackage
{
    using This = ConanPackage;

    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
