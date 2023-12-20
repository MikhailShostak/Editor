#pragma once

#include "Editor.hpp"

namespace DefaultExtensions
{

class TextEditor : public EditorAPI::Editor
{
public:
    void RenderFile(const std::filesystem::path &path) override;
};

}
