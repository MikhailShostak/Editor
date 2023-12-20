#pragma once

#include "Global.hpp"

class PUBLIC_API_EXPORT ImageGeneratorEditorView : public UI2::View
{
public:
    using Super = UI2::View;

    String Prompt = "Generate pixel art grassland landscape for top-down style game";
    String OutputPath = "Image.png";

    virtual void OnDraw(Graphics::Scene & Scene) override
    {
        if (ImGui::Begin("Image Generator Editor"))
        {
            ImGui::InputText("Prompt", &Prompt);
            ImGui::Text(g_OutputFolder.generic_string().data());
            ImGui::SameLine();
            ImGui::InputText("Output", &OutputPath);
            if (ImGui::Button("Generate"))
            {
                g_OpenAI.GenerateImage(g_OutputFolder / OutputPath, Prompt);
            }
        }
        ImGui::End();
    }
};
