#pragma once

#include "Global.hpp"

class PUBLIC_API_EXPORT ImageGeneratorSettingsView : public UI2::View
{
public:
    using Super = UI2::View;

    String OutputFolder;

    virtual void OnDraw(Graphics::Scene & Scene) override
    {
        ImGui::InputText("APIKey", &g_OpenAI.APIKey, ImGuiInputTextFlags_Password);
        OutputFolder = g_OutputFolder.generic_string();
        if (ImGui::InputText("OutputFolder", &OutputFolder))
        {
            g_OutputFolder = std::move(OutputFolder);
        }
    }
};
