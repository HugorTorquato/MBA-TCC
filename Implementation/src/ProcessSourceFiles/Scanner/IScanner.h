#pragma once

#include <memory>
#include <string>
#include <vector>
// #include <list>

#include "../util/LineFile.h"
#include "IToken.h"

class IScanner
{
   public:
    virtual ~IScanner() = default;

    virtual std::vector<std::shared_ptr<IToken>> scanTokens(const std::string& rawSourceCode) = 0;
};