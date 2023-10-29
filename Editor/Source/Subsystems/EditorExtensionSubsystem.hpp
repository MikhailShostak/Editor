#pragma once

struct PUBLIC_API_EXPORT EditorExtensionSubsystem
    : public Core::Subsystem, public EditorAPI::EditorContext
{
    using This = EditorExtensionSubsystem;
    using Super = Core::Subsystem;
    System::ExtensionLibrary<EditorAPI::EditorExtension> Extensions {};
    Map<String, ClassReference<EditorAPI::EditorFileEditor>> FileEditors {};
    Map<String, ClassReference<EditorAPI::EditorSettings>> Settings {};

    virtual ~EditorExtensionSubsystem() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Load();
    virtual void Unload();
    virtual void ShowExtensions();
    virtual void RegisterFileEditor(const String & Title, const ClassReference<EditorAPI::EditorFileEditor> & Editor);
    virtual void RegisterSettings(const String & Title, const ClassReference<EditorAPI::EditorSettings> & Settings);

    void Initialize()
    {
        Super::Initialize();
    }
};
