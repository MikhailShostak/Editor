#pragma once

namespace EditorAPI
{
struct PUBLIC_API_EXPORT EditorContext
{
    using This = EditorContext;

    virtual ~EditorContext() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RegisterFileEditor(const String & Title, const ClassReference<EditorAPI::EditorFileEditor> & Editor) {}
    virtual void RegisterSettings(const String & Title, const ClassReference<EditorAPI::EditorSettings> & Settings) {}

    void Initialize()
    {
    }
};
}
