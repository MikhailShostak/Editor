#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include <LegacyMath.hpp>
#include <LegacyFoundation.hpp>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct PUBLIC_API_EXPORT FileTemplate : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FileTemplate This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Name;
    String Description;
    Array<String> Extensions;
public:
    FileTemplate();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    std::function<void(const APath &directory, const String &name)> callback;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
