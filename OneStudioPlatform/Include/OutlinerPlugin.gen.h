#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include <LegacyMath.hpp>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
#include "OSPlugin.gen.h"
#include "Outliner.gen.h"

template<typename OutlinerViewType>
class PUBLIC_API_EXPORT OSOutlinerPlugin : public OSPlugin
{

    SharedReference<OutlinerViewType> outlinerView;

public:

    static_assert(std::is_base_of<OSOutliner, OutlinerViewType>::value, "OutlinerViewType should be type of OSOutliner");

    void load(const Map<String, OSPluginContext *> &dependentPlugins) override
    {
        outlinerView = CreateShared<OutlinerViewType>();
        //context->registerOutliner(outlinerView);
    }

    void unload() override
    {

    }

};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
