#include "ScannerForConditionMatch.h"

#include "../Logger/Log.h"
#include "util/ISourceReader.h"

ScannerForConditionMatch::ScannerForConditionMatch(
    json downloadResult,
    std::function<std::unique_ptr<ISourceReader>(const std::string& filePath)> sourceReaderFactory)
    : m_downloadResult(downloadResult), m_sourceReaderFactory(sourceReaderFactory)
{
    Logger::getInstance().log("[ScannerForConditionMatch::ScannerForConditionMatch]");
}

json ScannerForConditionMatch::downloadAndRetrieveSourceFileContent(const std::string& url) const
{
    Logger::getInstance().log("[ScannerForConditionMatch][downloadFilesInUrl] url: " + url +
                              " response: " + m_downloadResult.dump());

    json responseResult = json::object();

    for (auto& [key, path] : m_downloadResult.items())
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