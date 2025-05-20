#include <crow.h>

#include <memory>

#include "../../Logger/Log.h"
#include "../../ProcessSourceFiles/DownloadFiles.h"
#include "../../ProcessSourceFiles/ScannerForConditionMatch.h"
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

                    // Create a class here to handle this and make it testable...
                    // The route is just a bridge... and not suppose to have logic in here
                    DownloadFiles downoadFiles(git_url, std::make_unique<CurlHttpClient>());

                    json response = downoadFiles.downloadURLContentIntoTempFolder();
                    Logger::getInstance().log(
                        "[ProcessSourceFiles][downloadFilesInUrl] response: " + response.dump());

                    ScannerForConditionMatch scanner;
                    std::string readDocument = scanner.retrieveSourceFileContent(
                        SourceReaderAsString(downoadFiles.getTempFolder() + "/test.txt"));

                    Logger::getInstance().log(
                        "[ProcessSourceFiles][downloadFilesInUrl] response: " + readDocument);
                    return crow::response(readDocument);
                });
    }
};