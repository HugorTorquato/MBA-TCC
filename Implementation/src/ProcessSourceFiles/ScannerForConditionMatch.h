#pragma once

#include <string>

#include "IScanner.h"

class ScannerForConditionMatch : public IScanner
{
   public:
    ScannerForConditionMatch() = default;

    std::string retrieveSourceFileContent(const ISourceReader& reader) const override;
};