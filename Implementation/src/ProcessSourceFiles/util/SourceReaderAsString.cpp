#include "SourceReaderAsString.h"

#include <fstream>
#include <stdexcept>

std::string SourceReaderAsString::readFile(const std::string& filePath) const
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