#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct ExtensionDependency : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ExtensionDependency This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Package;
    String Version;
public:
    ExtensionDependency();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
