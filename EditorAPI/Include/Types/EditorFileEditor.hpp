#pragma once

namespace EditorAPI
{
struct PUBLIC_API_EXPORT EditorFileEditor
{
    using This = EditorFileEditor;

    virtual ~EditorFileEditor() {}
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
