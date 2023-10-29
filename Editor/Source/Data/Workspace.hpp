#pragma once

inline std::unordered_map<std::string, std::string> FileCache; //path, data
inline std::unordered_map<std::string, class Editor*> UnsavedFiles; //path, editor
inline bool PendingReindex = false;

inline Map<String, std::function<void()>> g_ToolBarItems;
inline Array<String> g_ActiveToolBarItems = {
    "File.New",
    "File.OpenFile",
    "File.OpenFolder",
    "File.Save",
    "Project.Selector",
    "Project.EditPackage",
    "Project.Clear",
    "Project.Build",
    "Project.Run",
};

std::string GetFileTitle(const std::filesystem::path &path, bool showExtensionOnly = false);

bool LoadFile(const std::filesystem::path &path);
bool LoadFolder(const std::filesystem::path &path);
void ReloadFiles();
void ReindexFiles();

void OpenFile(const std::filesystem::path &path, bool remember = true);
void SaveFile(const std::filesystem::path &source, const std::filesystem::path &destination);
void SaveFile(const std::filesystem::path &path);
void CloseFile(const std::filesystem::path &path, bool reindex = false);
void CloseFiles(const std::vector<std::filesystem::path> &paths);
void CloseAllFiles();

void OpenFolder(const std::filesystem::path &path, bool remember = true);
void CloseFolder(const std::filesystem::path &path, bool reindex = false);
void CloseFolders(const std::vector<std::filesystem::path> &paths);
void CloseAllFolders();

void OpenPath(const std::filesystem::path &path, bool remember = true);
void OpenPaths(const std::vector<std::filesystem::path> &paths, bool remember = true);

std::string &GetFileContent(const std::filesystem::path &path);
