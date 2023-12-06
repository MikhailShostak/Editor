#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include <LegacyMath.hpp>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
template<typename Type, typename ReturnType = SharedReference<Type>>
class PUBLIC_API_EXPORT AAllocator
{
    template<typename ExtendedType>
    static Type *staticAllocate()
    {
        return new ExtendedType();
    }

    Type *(*handle)() = nullptr;

public:

    template<typename ExtendedType>
    void setType()
    {
        handle = &staticAllocate<ExtendedType>;
    }

    ReturnType allocate() const
    {
        return staticAllocate();
    }

};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
