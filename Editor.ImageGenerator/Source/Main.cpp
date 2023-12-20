#include <EditorAPI.hpp>
#include "Main.hpp"

#include "ImageGeneratorEditor.hpp"
#include "ImageGeneratorSettingsView.hpp"

void Main::OnLoad(EditorAPI::EditorContext* Context)
{
    static Reflection::MetaObject<ImageGeneratorEditorView> ImageGeneratorEditorViewClass("ImageGeneratorEditorView");
    Context->RegisterWindow("ImageGeneratorEditorView", static_cast<ClassReference<UI2::View>>(&ImageGeneratorEditorViewClass));

    static Reflection::MetaObject<ImageGeneratorSettingsView> ImageGeneratorSettingsViewClass("ImageGeneratorSettingsView");
    Context->RegisterSettings("ImageGenerator", static_cast<ClassReference<UI2::View>>(&ImageGeneratorSettingsViewClass));
}

void Main::OnUnload()
{
    
}

REGISTER_EXTENSION(EditorAPI::EditorExtension, Main, 0.0.1, ImageGenerator);
