// File: fs_utils.h
#pragma once
#include <filesystem>
#include <string>

#include "../Logger/Log.h"

namespace inlineFreeFunctions
{

inline void deleteTempFolder(const std::filesystem::path& folderPath)
{
    Logger::getInstance().log("[deleteTempFolder] folderPath: " + folderPath.string());
    if (std::filesystem::exists(folderPath))
    {
        std::filesystem::remove_all(folderPath);
    }
}

}  // namespace inlineFreeFunctions