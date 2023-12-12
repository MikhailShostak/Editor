#pragma once

namespace EditorAPI
{

class PUBLIC_API_EXPORT Editor
{
public:
    virtual ~Editor() {}
    virtual void ResetIndex() {}
    virtual void IndexFile([[maybe_unused]] const System::Path &path) {}
    virtual void RenderFile([[maybe_unused]] const System::Path &path) {}
    virtual bool SaveFile([[maybe_unused]] const System::Path &source, [[maybe_unused]] const System::Path &destination) { return false; }

    template<typename T>
    void Serialize(T &&data)
    {
    }
};

}
