#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include <LegacyMath.hpp>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
#include <LegacyFoundation.hpp>
//#include <Experimental>

class OSFileSystemItem;

class PUBLIC_API_EXPORT OSOutliner
{

public:

    virtual ~OSOutliner() {}

    virtual UI::View *getView() const = 0;

    virtual void showItems(const Array<SharedReference<OSFileSystemItem>> &items) = 0;
    virtual void clear() = 0;

};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
