#include <EditorAPI.hpp>
#include "Main.hpp"

void Main::OnLoad(EditorAPI::EditorContext* Context)
{
    fmt::print("Main::OnLoad");
}

void Main::OnUnload()
{
    fmt::print("Main::OnUnload");
}

REGISTER_EXTENSION(EditorAPI::EditorExtension, Main, 0.0.1, TextEditor);
