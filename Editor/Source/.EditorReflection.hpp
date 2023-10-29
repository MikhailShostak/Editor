#pragma once

#include <EditorAPI.hpp>
#include ".Editor.hpp"
#include "Views/View/MainWindowView.hpp"
#include "Subsystems/EditorExtensionSubsystem.hpp"

namespace
{

struct EditorReflectionType
{
    EditorReflectionType()
    {
        Reflection::Add<MainWindowView>("MainWindowView");
        Reflection::Add<EditorSubsystem>("EditorSubsystem");
        Reflection::Add<EditorExtensionSubsystem>("EditorExtensionSubsystem");
    }
} inline EditorReflection;

}
