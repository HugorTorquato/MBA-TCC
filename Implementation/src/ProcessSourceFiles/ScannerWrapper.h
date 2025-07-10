#pragma once

#include <memory>
#include <string>

#include "IDownloadFiles.h"
#include "IScannerWrapper.h"
#include "util/ISourceReader.h"

class ScannerWrapper : public IScannerWrapper
{
   public:
    ScannerWrapper() = default;
    ScannerWrapper(json downloadResult,
                   std::function<std::unique_ptr<ISourceReader>(const std::string& filePath)>
                       sourceReaderFactory);

    json downloadAndRetrieveSourceFileContent(const std::string& url) const override;
    std::vector<std::pair<std::string, std::string>> evaluateJsonContent(
        const json& content) override;
    void groupTokensByFile(
        const std::vector<std::pair<std::string, std::string>> files_with_content);

   private:
    // Remove coupling from DownloadFiles, CurlHttpClient, and  SourceReaderAsString
    json m_downloadResult;
    std::function<std::unique_ptr<ISourceReader>(const std::string& filePath)>
        m_sourceReaderFactory;
};