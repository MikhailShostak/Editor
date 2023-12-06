#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include <LegacyMath.hpp>
#include <LegacyFoundation.hpp>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct DockEntry : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DockEntry This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Array<OneStudio::DockEntry> Entries;
    Array<String> WindowIdentifiers;
    SizeInteger WindowSize;
public:
    DockEntry();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION