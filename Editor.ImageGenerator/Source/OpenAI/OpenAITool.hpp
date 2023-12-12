#pragma once

#include "OpenAI/OpenAIResponse.hpp"
#include "OpenAI/OpenAIImageGeneratorResult.hpp"

class PUBLIC_API_EXPORT OpenAITool : public System::CommandLineTool
{
public:

    String APIKey;
    String ImageGenerationEndPoint = "https://api.openai.com/v1/images/generations";

    OpenAITool():
        CommandLineTool("C:/Windows/System32/curl.exe")
    {

    }

    void GenerateImage(const System::Path &OutputPath, const String &Prompt)
    {
        if (APIKey.empty())
        {
            return;
        }

        String Payload = "{ \"model\": \"dall-e-3\", \"quality\": \"hd\", \"prompt\": \"" + Prompt + "\", \"n\": 1, \"size\":\"1024x1024\" }";
        std::cout << Payload << std::endl;

        OpenAIResponse Response = System::GetOutputObject<OpenAIResponse>(
            Executable,
            ImageGenerationEndPoint,
            "-H", "Content-Type: application/json",
            "-H", "Authorization: Bearer " + APIKey,
            "-d", Payload
        );

        //OpenAIResponse Response;
        //Serialization::FromString("W:/response.json", Response);

        for (Serialization::Data &Data: Response.data)
        {
            OpenAIImageGeneratorResult Result;
            Serialization::Deserialize(Data, Result);
            std::cout << Result.url << std::endl;

            System::RunAndWait(Executable, Result.url, "-o", OutputPath.generic_string());
        }
    }
};
