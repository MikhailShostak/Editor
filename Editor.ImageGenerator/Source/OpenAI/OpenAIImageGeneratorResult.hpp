#pragma once

struct PUBLIC_API_EXPORT OpenAIImageGeneratorResult
{
    using This = OpenAIImageGeneratorResult;
    String revised_prompt {};
    String url {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["revised_prompt"] & revised_prompt;
        data["url"] & url;
    }

    void Initialize()
    {
    }
};
