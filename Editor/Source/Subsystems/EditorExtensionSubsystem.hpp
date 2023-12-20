#pragma once

struct PUBLIC_API_EXPORT EditorExtensionSubsystem
    : public EditorAPI::EditorContext
{
    using This = EditorExtensionSubsystem;
    using Super = EditorAPI::EditorContext;
    System::ExtensionLibrary<EditorAPI::EditorExtension> Extensions {};
    Map<String, ClassReference<EditorAPI::Editor>> FileEditors {};
    Map<String, ClassReference<EditorAPI::EditorSettings>> Settings {};

    virtual ~EditorExtensionSubsystem() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Load();
    virtual void Unload();
    virtual void ShowExtensions();
    virtual void RegisterFileEditor(const String & Title, const ClassReference<EditorAPI::Editor> & Editor);
    virtual void RegisterSettings(const String & Title, const ClassReference<UI2::View> & Settings);
    virtual void RegisterWindow(const String & Title, const ClassReference<UI2::View> & View);
    virtual void MarkFileDirty(const System::Path & Path, const EditorAPI::Editor & Editor);

    void Initialize()
    {
        Super::Initialize();
    }
};
