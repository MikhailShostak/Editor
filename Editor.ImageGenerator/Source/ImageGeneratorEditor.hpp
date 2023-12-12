#pragma once

#include "OpenAI/OpenAITool.hpp"

class PUBLIC_API_EXPORT ImageGeneratorEditorView : public UI2::View
{
public:
    using Super = UI2::View;

    OpenAITool OpenAI;
    String Prompt = "Generate pixel art grassland landscape for top-down style game";
    String OutputPath = "W:/Image.png";

    ImageGeneratorEditorView()
    {

    }

    virtual void OnDraw(Graphics::Scene & Scene) override
    {
        if (ImGui::Begin("Image Generator Editor"))
        {
            ImGui::InputText("APIKey", &OpenAI.APIKey);
            ImGui::InputText("Prompt", &Prompt);
            ImGui::InputText("Output", &OutputPath);
            if (ImGui::Button("Generate"))
            {
                OpenAI.GenerateImage(OutputPath, Prompt);
            }
        }
        ImGui::End();
    }
};
