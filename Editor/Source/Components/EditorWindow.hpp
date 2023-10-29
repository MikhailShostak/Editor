#pragma once

struct PUBLIC_API_EXPORT EditorWindow
    : public Graphics::RenderingSubsystem
{
    using This = EditorWindow;
    using Super = Graphics::RenderingSubsystem;
    SharedReference<System::ConfigFile<EditorConfig>> Config {};

    virtual ~EditorWindow() {}
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
