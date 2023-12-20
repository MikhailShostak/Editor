namespace Settings
{

class EnvironmentView : public UI2::View
{
public:

void OnDraw(Graphics::Scene &Scene) override
{
    if (ImGui::BeginTable("EnvironmentTable", 2, DefaultTableFlags))
    {
        ImGui::TableSetupColumn("Variable", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();
        auto env = boost::this_process::environment();
        for(const auto &e : env)
        {
            if(e.get_name().empty())
            {
                continue;
            }

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(e.get_name().data());
            ImGui::TableSetColumnIndex(1);
            std::vector<std::string> strings = e.to_vector();
            for(const auto &s : strings)
            {
                ImGui::TextWrapped("%s", s.data());
            }

        }

        ImGui::EndTable();
    }
}

};

}
