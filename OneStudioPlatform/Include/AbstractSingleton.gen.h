#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include <LegacyMath.hpp>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
template<typename Type>
struct PUBLIC_API_EXPORT AbstractSingleton
{
public:
    static Type &getInstance()
    {
        Type *singleton = reinterpret_cast<Type *>(ASingletonStorage::findSingleton(typeid(Type).hash_code()));
        AAssert(singleton, "Singleton is undefined");
        return *singleton;
    }

    template<typename ReturnType>
    static ReturnType& getInstanceAs()
    {
        return static_cast<ReturnType &>(getInstance());
    }

    template<typename DerivedType>
    static DerivedType &createInstance()
    {
        static_assert(std::is_base_of_v<Type, DerivedType>, "DerivedType is not derived class of Type");
        static DerivedType singleton;
        return singleton;
    }

protected:
    AbstractSingleton()
    {
        AAssert(!ASingletonStorage::findSingleton(typeid(Type).hash_code()), "Singleton already exists");
        ASingletonStorage::registerSingleton(typeid(Type).hash_code(), static_cast<Type *>(this));
    }
};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
