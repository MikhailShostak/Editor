#pragma once

#include "Editor.hpp"

namespace DefaultExtensions
{

class BinaryEditor : public EditorAPI::Editor
{
public:
    void RenderFile(const std::filesystem::path &path) override;
};

}
