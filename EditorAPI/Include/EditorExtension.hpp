#pragma once

namespace EditorAPI
{
struct PUBLIC_API_EXPORT EditorExtension
{
    using This = EditorExtension;

    virtual ~EditorExtension() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnLoad(EditorContext* Context) {}
    virtual void OnUnload() {}

    void Initialize()
    {
    }
};
}
