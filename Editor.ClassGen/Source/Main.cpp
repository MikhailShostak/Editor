#include <EditorAPI.hpp>
#include "Main.hpp"

#include "Editor/ClassGenEditor.hpp"

void Main::OnLoad(EditorAPI::EditorContext* Context)
{
    static Reflection::MetaObject<DefaultExtensions::ClassGenEditor> EditorClass("ClassGenEditor");
    Context->RegisterFileEditor("ClassGenEditor", static_cast<ClassReference<EditorAPI::Editor>>(&EditorClass));
}

void Main::OnUnload()
{
    
}

REGISTER_EXTENSION(EditorAPI::EditorExtension, Main, 0.0.1, ClassGen);
