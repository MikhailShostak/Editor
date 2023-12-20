#pragma once

namespace EditorAPI
{
struct PUBLIC_API_EXPORT EditorContext
    : public Core::Subsystem
{
    using This = EditorContext;
    using Super = Core::Subsystem;

    virtual ~EditorContext() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RegisterFileEditor(const String & Title, const ClassReference<EditorAPI::Editor> & Editor) = 0;
    virtual void RegisterSettings(const String & Title, const ClassReference<UI2::View> & Settings) = 0;
    virtual void RegisterWindow(const String & Title, const ClassReference<UI2::View> & View) = 0;
    virtual void MarkFileDirty(const System::Path & Path, const EditorAPI::Editor & Editor) = 0;

    void Initialize()
    {
        Super::Initialize();
    }
};
}
