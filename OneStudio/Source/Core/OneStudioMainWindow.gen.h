//CLASSGEN GENERATED REGION: Includes
#include <LegacyExperimental.hpp>
#include <Graphics>
#include <LegacyFoundation.hpp>
#include <MainViewAsset.gen.h>
#include <LegacyMath.hpp>
#include <LegacyMath.hpp>

//CLASSGEN END REGION
#include <UI2>
//CLASSGEN GENERATED REGION: Implementation
namespace OneStudio{
inline DynamicAsset<Core::Window2> OneStudioMainWindow_Asset = DynamicAsset<Core::Window2>("OneStudio.OneStudioMainWindow", [](auto &asset){
UI::UIComposition* composition_0 = Create<UI::UIComposition>();
(*composition_0).setRoot(OneStudio::MainViewAsset_Asset.load());
asset.setComposition(composition_0);
asset.setTitle("One Studio");
Math::IntegerVector initialSize_3;
initialSize_3.X = 800.000000;
initialSize_3.Y = 480.000000;
asset.setInitialSize(initialSize_3);
});
}
//CLASSGEN END REGION