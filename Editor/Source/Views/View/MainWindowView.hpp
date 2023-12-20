#pragma once

class MainWindowView : public UI2::View
{
public:
    using Super = UI2::View;

    void Draw(Graphics::Scene & Scene) override;
};
