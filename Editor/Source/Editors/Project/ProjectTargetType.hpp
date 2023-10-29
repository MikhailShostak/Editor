#pragma once

enum class ProjectTargetType
{
    Application,
    SharedLibrary,
    StaticLibrary,
    Interface,
};

namespace Serialization
{
template<>
struct Serializer<InputValue, ProjectTargetType>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue&& data, ValueType&& value)
    {
        if (data.m_Storage.IsScalar())
        {
            const auto &valueName = data.m_Storage.template as<std::string>();
            if (valueName == "Application") { value = ProjectTargetType::Application; return; }
            if (valueName == "SharedLibrary") { value = ProjectTargetType::SharedLibrary; return; }
            if (valueName == "StaticLibrary") { value = ProjectTargetType::StaticLibrary; return; }
            if (valueName == "Interface") { value = ProjectTargetType::Interface; return; }
            value = ProjectTargetType::Application;

        }
    }
};

template<>
struct Serializer<OutputValue, ProjectTargetType>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue&& data, ValueType&& value)
    {

        switch(value)
        {
        case ProjectTargetType::Application: data.m_Storage = "Application"; return;
        case ProjectTargetType::SharedLibrary: data.m_Storage = "SharedLibrary"; return;
        case ProjectTargetType::StaticLibrary: data.m_Storage = "StaticLibrary"; return;
        case ProjectTargetType::Interface: data.m_Storage = "Interface"; return;
        }

    }
};

}
