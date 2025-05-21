#include "ScannerForConditionMatch.h"

#include "../Logger/Log.h"
#include "util/ISourceReader.h"

ScannerForConditionMatch::ScannerForConditionMatch(
    std::shared_ptr<IDownloadFiles> downloader,
    std::function<std::unique_ptr<ISourceReader>(const std::string& filePath)> sourceReaderFactory)
    : m_downloadFiles(downloader), m_sourceReaderFactory(sourceReaderFactory)
{
    Logger::getInstance().log("[ScannerForConditionMatch::ScannerForConditionMatch]");
}

json ScannerForConditionMatch::downloadAndRetrieveSourceFileContent(const std::string& url) const
{
    Logger::getInstance().log(
        "[ScannerForConditionMatch][downloadAndRetrieveSourceFileContent] url: " + url);

    json downloadResult = m_downloadFiles->downloadURLContentIntoTempFolder();
    Logger::getInstance().log("[ScannerForConditionMatch][downloadFilesInUrl] response: " +
                              downloadResult.dump());

    json responseResult = json::object();

    for (auto& [key, path] : downloadResult.items())
    {
        if (key.rfind("root", 0) == 0) continue;

        auto reader = m_sourceReaderFactory(path);
        std::string readDocument = reader->readFile();

        Logger::getInstance().log(
            "[ScannerForConditionMatch][downloadAndRetrieveSourceFileContent] readDocument: " +
            readDocument);

        responseResult[key] = readDocument;
    }

    return responseResult;
}