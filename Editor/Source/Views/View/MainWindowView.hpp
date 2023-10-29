#pragma once

class MainWindowView : public UI2::View
{
public:
    using Super = UI2::View;

    MainWindowView()
    {
        Views.push_back(std::make_shared<ImageGeneratorEditorView>());
        Views.push_back(std::make_shared<PackageManagerView>());
    }
};
