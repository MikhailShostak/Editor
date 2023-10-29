#pragma once

#include "Editors/Editor.hpp"

namespace DefaultExtensions
{

class ProjectEditor : public Editor
{
public:
    ProjectEditor();
    void IndexFile(const System::Path& path) override;
    void RenderFile(const System::Path& path) override;
    bool SaveFile(const System::Path& source, const System::Path& destination) override;
};

}
