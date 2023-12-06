#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <LegacyExperimental.hpp>

#include <LegacyFoundation.hpp>
#include <LegacyExperimental.hpp>

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class OpenFileView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef OpenFileView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    OpenFileView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::PathField> pathField;
    SharedReference<UI::TextButton> openButton;
    SharedReference<UI::TextButton> cancelButton;
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION