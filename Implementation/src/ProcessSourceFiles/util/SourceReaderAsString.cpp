#include "SourceReaderAsString.h"

#include <fstream>
#include <stdexcept>

#include "../../Logger/Log.h"

// TODO:
// - Create an arg checker for path. To nthandle it as strings anymore
namespace
{
std::string readFile(const std::string& filePath)
{
    std::ifstream file(filePath);  // Open the file using an input file stream (ifstream)
    if (!file.is_open())
    {
        throw std::runtime_error("[SourceReaderAsString::readFile] Could not open file: " +
                                 filePath);
    }

    // Read the entire file into a std::string using stream buffer iterators
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
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