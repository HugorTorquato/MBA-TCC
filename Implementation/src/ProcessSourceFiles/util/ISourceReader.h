#pragma once

#include <string>

class ISourceReader
{
   public:
    virtual ~ISourceReader() = default;

    virtual std::string readFile() const = 0;
    virtual std::string readFile(const std::string& filePath) const = 0;
};