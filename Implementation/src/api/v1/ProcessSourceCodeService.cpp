// ProcessSourceCodeService.cpp
#include "ProcessSourceCodeService.h"

#include "../../Logger/Log.h"
#include "../../ProcessSourceFiles/ContainersInterface/ContainersInterface.h"
#include "../../ProcessSourceFiles/DownloadFiles.h"
#include "../../ProcessSourceFiles/Parser/Parser.h"
#include "../../ProcessSourceFiles/Scanner/Scanner.h"
#include "../../ProcessSourceFiles/ScannerCoordinator.h"
#include "../../ProcessSourceFiles/util/HttpClient.h"
#include "../../ProcessSourceFiles/util/SourceReaderAsString.h"

nlohmann::json ProcessSourceCodeService::process(const std::string& gitUrl)
{
    Logger::getInstance().log("[ProcessSourceCodeService::process] gitUrl: " + gitUrl);

    auto downloader = std::make_shared<DownloadFiles>(gitUrl, std::make_unique<CurlHttpClient>());
    auto readerFactory = [](const std::string& path)
    { return std::make_unique<SourceReaderAsString>(path); };

    ScannerCoordinator scanner(downloader->downloadURLContentIntoTempFolder(), readerFactory);
    auto jsonResult = scanner.downloadAndRetrieveSourceFileContent(gitUrl);
    Logger::getInstance().log("[ProcessSourceCodeService::process] jsonResult: " +
                              jsonResult.dump());

    auto scannerResult = scanner.evaluateJsonContent(jsonResult);

    for (const auto& [fileName, content] : scannerResult)
    {
        Logger::getInstance().log("[ProcessSourceCodeService::process] fileName: " + fileName +
                                  " content: " + content);

        Scanner scanner(content);
        auto tokens = scanner.scanTokens(content, fileName);
        for (const auto& token : tokens)
        {
            Logger::getInstance().log("[ProcessSourceCodeService::process] token: " +
                                      (token ? token->toString() : "nullptr"));
        }

        Parser parser(tokens);
        auto parserResults = parser.parseAll();

        for (const auto& result : parserResults)
        {
            if (auto parsedResult = std::dynamic_pointer_cast<ClassST>(result))
            {
                ContainersInterface::getInstance().addClass(parsedResult);
                Logger::getInstance().log(
                    "[ProcessSourceCodeService::process] Parsed Class Name: " +
                    parsedResult->getClassName());
            }
        }
    }

    nlohmann::json classesJson = nlohmann::json::array();
    for (const auto& classST : ContainersInterface::getInstance().getClasses())
    {
        Logger::getInstance().log("[ProcessSourceCodeService::process] Parser Result: " +
                                  classST->toString());
        nlohmann::json classInfo;
        classInfo["className"] = classST->getClassName();

        nlohmann::json inherencyArray = nlohmann::json::array();
        for (const auto& pair : classST->getInherencyArray())
        {
            nlohmann::json pairJson;
            if (pair.first)
            {
                pairJson["first"] = {
                    {"type", TokenTypeNameSpace::toString(pair.first->getTypeEnum())},
                    {"lexeme", pair.first->getLexeme()}};
            }
            if (pair.second)
            {
                pairJson["second"] = {
                    {"type", TokenTypeNameSpace::toString(pair.second->getTypeEnum())},
                    {"lexeme", pair.second->getLexeme()}};
            }
            inherencyArray.push_back(pairJson);
        }

        classInfo["inherency"] = inherencyArray;
        classesJson.push_back(classInfo);
    }

    Logger::getInstance().log("[ProcessSourceCodeService::process] classesJson: " +
                              classesJson.dump());
    return classesJson;
}
