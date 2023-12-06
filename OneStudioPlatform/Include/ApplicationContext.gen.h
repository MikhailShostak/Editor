#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include <LegacyMath.hpp>

//CLASSGEN END REGION
#include <LegacyFoundation.hpp>
#include "AbstractSingleton.gen.h"
#include "Task.gen.h"
#include "FileSystemObserver.gen.h"
#include "FileTemplate.gen.h"

class OSPlugin;
class OSOutliner;
class OSControlVersionSystem;
class OSFileSystemItem;
namespace UI
{
class View;
class Menu;
}
class AEventDispatcher;
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class PUBLIC_API_EXPORT ApplicationContext : public AbstractSingleton<ApplicationContext>
{
public:
    virtual APath getDeveloperDirectory() const = 0;
    virtual APath getLibraryDirectory() const = 0;

    virtual bool registerCommand(const String &command, const std::function<void(const Array<String> &arguments)> &callback) = 0;
    virtual bool registerOutliner(const SharedReference<OSOutliner> &outliner) = 0;
    virtual bool registerControlVersionSystem(const SharedReference<OSControlVersionSystem> &cvs) = 0;
    virtual bool registerToolBarItem(const String &identifier, SharedReference<UI::View> const &view) = 0;
    virtual bool registerWindow(const String &title, SharedReference<UI::View> const &view) = 0;

    virtual void showProperties(UI::View *view) = 0;

    virtual void print(const String &text) = 0;
    virtual void log(const String &text, const String &file = String(), const String &indication = String()) = 0;
    virtual void warning(const String &text, const String &file = String(), const String &indication = String()) = 0;
    virtual void error(const String &text, const String &file = String(), const String &indication = String()) = 0;

    //minor fixes
    virtual void loadExtension(const Path &path) = 0;
    virtual void unloadExtension(const String &package) = 0;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
