#include "ScannerForConditionMatch.h"

#include "../Logger/Log.h"
#include "../ProcessSourceFiles/util/SourceReaderAsString.h"
#include "DownloadFiles.h"
#include "util/HttpClient.h"
#include "util/ISourceReader.h"

json ScannerForConditionMatch::downloadAndRetrieveSourceFileContent(const std::string& url) const
{
    // return reader.readFile();

    DownloadFiles downoadFiles(url, std::make_unique<CurlHttpClient>());

    json downloadResult = downoadFiles.downloadURLContentIntoTempFolder();
    Logger::getInstance().log("[ProcessSourceFiles][downloadFilesInUrl] response: " +
                              downloadResult.dump());

    json responseResult = json::object();

    for (auto& [key, path] : downloadResult.items())
    {
        if (key.rfind("root", 0) == 0) continue;

        std::unique_ptr<ISourceReader> reader = std::make_unique<SourceReaderAsString>(path);
        std::string readDocument = reader->readFile();

        Logger::getInstance().log("[ProcessSourceFiles][downloadFilesInUrl] readDocument: " +
                                  readDocument);

        responseResult[key] = readDocument;
    }

    return responseResult;
}