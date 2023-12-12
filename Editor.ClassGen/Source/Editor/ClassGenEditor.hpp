#pragma once

#include <EditorAPI.hpp>

namespace DefaultExtensions
{

class ClassGenEditor : public EditorAPI::Editor
{
public:
    using Super = EditorAPI::Editor;
    using This = ClassGenEditor;
    void ResetIndex() override;
    void IndexFile(const System::Path &path) override;
    void RenderFile(const System::Path &path) override;
    bool SaveFile(const System::Path &source, const System::Path &destination) override;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};

}
