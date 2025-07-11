#pragma once

#include "IScanner.h"

class Scanner : public IScanner
{
   public:
    Scanner() = default;

    // Scan tokens from the raw source code
    std::vector<std::string> scanTokens(const std::string& rawSourceCode) const override;

   private:
    // Add any private members or methods if needed
};