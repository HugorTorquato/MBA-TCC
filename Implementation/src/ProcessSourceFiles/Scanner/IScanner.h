#pragma once

#include <string>
#include <vector>

class IScanner
{
   public:
    virtual ~IScanner() = default;

    virtual std::vector<std::string> scanTokens(const std::string& rawSourceCode) const = 0;
};