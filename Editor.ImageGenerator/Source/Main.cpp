#include <EditorAPI.hpp>
#include "Main.hpp"

#include "ImageGeneratorEditor.hpp"

void Main::OnLoad(EditorAPI::EditorContext* Context)
{
    static Reflection::MetaObject<ImageGeneratorEditorView> ImageGeneratorEditorViewClass("ImageGeneratorEditorView");
    Context->RegisterWindow("ImageGeneratorEditorView", static_cast<ClassReference<UI2::View>>(&ImageGeneratorEditorViewClass));
}

void Main::OnUnload()
{
    
}

REGISTER_EXTENSION(EditorAPI::EditorExtension, Main, 0.0.1, ImageGenerator);
