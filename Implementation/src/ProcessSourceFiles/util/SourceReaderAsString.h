#pragma once

#include "ISourceReader.h"

class SourceReaderAsString : public ISourceReader
{
   public:
    SourceReaderAsString() = delete;
    SourceReaderAsString(const std::string& filePath);

    std::string readFile() const override;
    std::string readFile(const std::string& filePath) const override;

   private:
    std::string m_filePath;
};