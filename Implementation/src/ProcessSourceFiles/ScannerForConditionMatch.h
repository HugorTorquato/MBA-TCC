#pragma once

#include <memory>
#include <string>

#include "IDownloadFiles.h"
#include "IScanner.h"
#include "util/ISourceReader.h"

class ScannerForConditionMatch : public IScanner
{
   public:
    ScannerForConditionMatch() = default;
    ScannerForConditionMatch(
        json downloadResult,
        std::function<std::unique_ptr<ISourceReader>(const std::string& filePath)>
            sourceReaderFactory);

    json downloadAndRetrieveSourceFileContent(const std::string& url) const override;

   private:
    // Remove coupling from DownloadFiles, CurlHttpClient, and  SourceReaderAsString
    json m_downloadResult;
    std::function<std::unique_ptr<ISourceReader>(const std::string& filePath)>
        m_sourceReaderFactory;
};