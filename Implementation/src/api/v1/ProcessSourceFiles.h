#include <crow.h>

#include <memory>

#include "../../Logger/Log.h"
#include "../../ProcessSourceFiles/DownloadFiles.h"
#include "../../ProcessSourceFiles/Parser/Parser.h"
#include "../../ProcessSourceFiles/Scanner/Scanner.h"
#include "../../ProcessSourceFiles/ScannerCoordinator.h"
#include "../../ProcessSourceFiles/util/HttpClient.h"
#include "../../ProcessSourceFiles/util/SourceReaderAsString.h"

class ProcessSourceFiles
{
   public:
    void setup_ProcessSourceFiles_Routes(crow::SimpleApp& app)
    {
        Logger::getInstance().log("Starting Process Source Files Routes.");

        // Route to receive an URL ( path or path to file )
        process_Source_Files_From_GIT_URL(app);
    }

   private:
    void process_Source_Files_From_GIT_URL(crow::SimpleApp& app)
    {
        CROW_ROUTE(app, "/api/v1/process")
            .methods("POST"_method)(
                [](const crow::request& req)
                {
                    Logger::getInstance().log("Accessing /api/v1/process route.");
                    auto body = crow::json::load(req.body);

                    if (!body) return crow::response(400, "Invalid JSON");

                    std::string git_url = body["url"].s();

                    // Create a class here to handle this and make it testable...
                    // The route is just a bridge... and not suppose to have logic in here

                    return crow::response("Received GitHub URL: " + git_url);
                });

        CROW_ROUTE(app, "/api/v1/listFilesInUrl")
            .methods("POST"_method)(
                [](const crow::request& req)
                {
                    Logger::getInstance().log("Accessing /api/v1/listFilesInUrl route.");
                    auto body = crow::json::load(req.body);

                    if (!body) return crow::response(400, "Invalid JSON");

                    const std::string git_url = body["url"].s();

                    // Create a class here to handle this and make it testable...
                    // The route is just a bridge... and not suppose to have logic in here
                    DownloadFiles downoadFiles(git_url, std::make_unique<CurlHttpClient>());

                    return crow::response(
                        downoadFiles.listGitHubContentFromURL(downoadFiles.getOriginalURL()));
                });

        CROW_ROUTE(app, "/api/v1/downloadFilesInUrl")
            .methods("POST"_method)(
                [](const crow::request& req)
                {
                    Logger::getInstance().log("Accessing /api/v1/downloadFilesInUrl route.");
                    auto body = crow::json::load(req.body);

                    if (!body) return crow::response(400, "Invalid JSON");

                    const std::string git_url = body["url"].s();

                    // Create a class here to handle this and make it testable...
                    // The route is just a bridge... and not suppose to have logic in here
                    DownloadFiles downoadFiles(git_url, std::make_unique<CurlHttpClient>());

                    json response = downoadFiles.downloadURLContentIntoTempFolder();

                    Logger::getInstance().log(
                        "[ProcessSourceFiles][downloadFilesInUrl] response: " + response.dump());
                    return crow::response(response.dump());
                });

        CROW_ROUTE(app, "/api/v1/downloadAndRetreveSourceFileContent")
            .methods("POST"_method)(
                [](const crow::request& req)
                {
                    Logger::getInstance().log(
                        "Accessing /api/v1/downloadAndRetreveSourceFileContent route.");
                    auto body = crow::json::load(req.body);

                    if (!body) return crow::response(400, "Invalid JSON");

                    const std::string git_url = body["url"].s();

                    auto downloader = std::make_shared<DownloadFiles>(
                        git_url, std::make_unique<CurlHttpClient>());

                    auto readerFactory = [](const std::string& path)
                    { return std::make_unique<SourceReaderAsString>(path); };

                    ScannerCoordinator scanner(downloader->downloadURLContentIntoTempFolder(),
                                               readerFactory);
                    json jsonResult = scanner.downloadAndRetrieveSourceFileContent(git_url);

                    Logger::getInstance().log(
                        "[ProcessSourceFiles][downloadAndRetreveSourceFileContent] response: " +
                        jsonResult.dump());
                    return crow::response(jsonResult.dump());
                });

        CROW_ROUTE(app, "/api/v1/processSourceCode")
            .methods("POST"_method)(
                [](const crow::request& req)
                {
                    Logger::getInstance().log("Accessing /api/v1/processSourceCode route.");
                    auto body = crow::json::load(req.body);

                    if (!body) return crow::response(400, "Invalid JSON");

                    const std::string source_code = "";
                    const std::string git_url = body["url"].s();

                    crow::json::wvalue res;
                    res["message"] = "Received Source Code";
                    res["length"] = source_code.length();

                    auto readerFactory = [](const std::string& path)
                    { return std::make_unique<SourceReaderAsString>(path); };

                    // Instanciar o downloader
                    auto downloader = std::make_shared<DownloadFiles>(
                        git_url, std::make_unique<CurlHttpClient>());
                    // Instanciar o scanner
                    ScannerCoordinator scanner(downloader->downloadURLContentIntoTempFolder(),
                                               readerFactory);
                    // Processar o source file e retornar o json
                    json jsonResult = scanner.downloadAndRetrieveSourceFileContent(git_url);

                    Logger::getInstance().log(
                        "[ProcessSourceFiles][downloadAndRetreveSourceFileContent] response: " +
                        jsonResult.dump());

                    // TODO: Add logic to trigger the scanner and parser

                    // Scanner

                    auto scannerResult = scanner.evaluateJsonContent(jsonResult);

                    // ScanTokens
                    for (const auto& [fileName, content] : scannerResult)
                    {
                        Logger::getInstance().log(
                            "[ProcessSourceFiles][processSourceCode] fileName: " + fileName +
                            " content: " + content);

                        Scanner scanner(content);
                        auto tokens = scanner.scanTokens(content, fileName);

                        Logger::getInstance().log(
                            "[ProcessSourceFiles][processSourceCode] Tokens for file: " + fileName);

                        for (const auto& token : tokens)
                        {
                            Logger::getInstance().log(
                                "[ProcessSourceFiles][processSourceCode] token: " +
                                (token ? token->toString() : "nullptr"));
                        }

                        // Parser
                        Parser parser(tokens);
                        auto parserResults = parser.parseAll();
                        std::shared_ptr<ClassST> parsedResult;

                        for (const auto& result : parserResults)
                        {
                            parsedResult = std::dynamic_pointer_cast<ClassST>(result);
                            Logger::getInstance().log(
                                "[ProcessSourceFiles][processSourceCode] Parser Result: " +
                                (parsedResult ? parsedResult->toString() : "nullptr"));

                            if (parsedResult)
                            {
                                Logger::getInstance().log(
                                    "[ProcessSourceFiles][processSourceCode] Parsed Class Name: " +
                                    parsedResult->getClassName());
                                ContainersInterface::getInstance().addClass(parsedResult);
                            }
                        }
                    }

                    auto classes = ContainersInterface::getInstance().getClasses();
                    for (const auto& classST : classes)
                    {
                        Logger::getInstance().log(
                            "[ProcessSourceFiles][processSourceCode] Stored Class Name: " +
                            classST->getClassName());
                    }

                    // Parser parser(scannerResult);

                    json classesJson = json::array();
                    for (const auto& classST : classes)
                    {
                        json classInfo;
                        classInfo["className"] = classST->getClassName();

                        // build inherency array
                        json inherencyArray = json::array();
                        for (const auto& pair : classST->getInherencyArray())
                        {
                            json pairJson;

                            if (pair.first)
                            {
                                pairJson["first"] = {
                                    {"type",
                                     TokenTypeNameSpace::toString(
                                         pair.first
                                             ->getTypeEnum())},  // or
                                                                 // toString(pair.first->getType())
                                    {"lexeme", pair.first->getLexeme()}};
                            }

                            if (pair.second)
                            {
                                pairJson["second"] = {{"type", TokenTypeNameSpace::toString(
                                                                   pair.second->getTypeEnum())},
                                                      {"lexeme", pair.second->getLexeme()}};
                            }

                            inherencyArray.push_back(pairJson);
                        }

                        classInfo["inherency"] = inherencyArray;
                        classesJson.push_back(classInfo);
                    }

                    Logger::getInstance().log(
                        "[ProcessSourceFiles][processSourceCode] classesJson: " +
                        classesJson.dump());
                    Logger::getInstance().log("Ending /api/v1/processSourceCode route.");
                    return crow::response(classesJson.dump());
                });
    }
};