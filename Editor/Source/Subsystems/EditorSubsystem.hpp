#pragma once

struct PUBLIC_API_EXPORT EditorSubsystem
    : public Graphics::RenderingSubsystem
{
    using This = EditorSubsystem;
    using Super = Graphics::RenderingSubsystem;
    System::ConfigFile<EditorConfig> Config {};

    virtual ~EditorSubsystem() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Config"] & Config;
    }
    virtual void Load();
    virtual void Unload();
    virtual void CreateUI();
    virtual void RenderScene(Graphics::Window & Window, Graphics::Scene & Scene);

    void Initialize()
    {
        Super::Initialize();
    }
};
