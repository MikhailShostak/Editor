#pragma once

struct PUBLIC_API_EXPORT Main
    : public EditorAPI::EditorExtension
{
    using This = Main;
    using Super = EditorAPI::EditorExtension;

    virtual ~Main() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnLoad(EditorAPI::EditorContext* Context);
    virtual void OnUnload();

    void Initialize()
    {
        Super::Initialize();
    }
};
