#pragma once

namespace EditorAPI
{
struct PUBLIC_API_EXPORT EditorSettings
{
    using This = EditorSettings;

    virtual ~EditorSettings() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnDraw() {}

    void Initialize()
    {
    }
};
}
