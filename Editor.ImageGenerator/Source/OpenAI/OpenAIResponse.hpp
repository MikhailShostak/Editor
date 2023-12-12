#pragma once

struct PUBLIC_API_EXPORT OpenAIResponse
{
    using This = OpenAIResponse;
    uint64_t created {};
    Array<Serialization::Data> data {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["created"] & created;
        data["data"] & this->data;
    }

    void Initialize()
    {
    }
};
