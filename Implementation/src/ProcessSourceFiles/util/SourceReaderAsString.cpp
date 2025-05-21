#include "SourceReaderAsString.h"

#include <fstream>
#include <stdexcept>
#include <string>

#include "../../Logger/Log.h"

// TODO:
// - Create an arg checker for path. To nthandle it as strings anymore
namespace
{
std::string readFile(const std::string& filePath)
{
    if (filePath.empty())
    {
        throw std::invalid_argument("[::readFile] File path is empty");
    }

    std::filesystem::path basePath("/app/temp");
    std::filesystem::path fullPath = basePath / filePath;

    if (!std::filesystem::exists(fullPath))
    {
        throw std::runtime_error("[::readFile] File does not exist: " + fullPath.string());
    }

    Logger::getInstance().log("[::readFile] fullPath: " + fullPath.string());

    std::ifstream file(fullPath,
                       std::ios::in | std::ios::binary);  // Open in binary mode for robustness

    if (!file.is_open())
    {
        throw std::runtime_error("[::readFile] Could not open file: " + fullPath.string());
    }

    // Use a stringstream for better performance and readability
    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    return contentStream.str();
}
}  // namespace

SourceReaderAsString::SourceReaderAsString(const std::string& filePath) : m_filePath(filePath)
{
    Logger::getInstance().log("[SourceReaderAsString::SourceReaderAsString] filePath: " + filePath);
    if (filePath.empty())
    {
        throw std::invalid_argument(
            "[SourceReaderAsString::SourceReaderAsString] File path is empty");
    }
}

std::string SourceReaderAsString::readFile() const
{
    Logger::getInstance().log("[SourceReaderAsString::readFile] filePath: " + m_filePath);
    return ::readFile(m_filePath);
}

std::string SourceReaderAsString::readFile(const std::string& filePath) const
{
    Logger::getInstance().log("[SourceReaderAsString::readFile w/ parameter] filePath: " +
                              filePath);
    if (filePath.empty())
    {
        throw std::invalid_argument(
            "[SourceReaderAsString::readFile w/ parameter] File path is empty");
    }

    return ::readFile(filePath);
}
