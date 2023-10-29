#pragma once

struct ProjectEditablePackage
{
    using This = ProjectEditablePackage;
    System::Path path = {};
    System::Path layout = {};
    System::Path output_folder = {};

    virtual ~ProjectEditablePackage() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["path"] & path;
        data["layout"] & layout;
        data["output_folder"] & output_folder;
    }

    void Initialize()
    {
    }
};
