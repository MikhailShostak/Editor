#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "FunctionInfo.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct EventSet : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EventSet This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Array<LegacyClassGen::FunctionInfo> Events;
public:
    EventSet();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
