#pragma once

#include "ISourceReader.h"

class SourceReaderAsString : public ISourceReader
{
   public:
    SourceReaderAsString() = default;

    std::string readFile(const std::string& filePath) const override;
};