#pragma once

#include <string>

#include "IScanner.h"

class ScannerForConditionMatch : public IScanner
{
   public:
    ScannerForConditionMatch() = default;

    json downloadAndRetrieveSourceFileContent(const std::string& url) const override;
};