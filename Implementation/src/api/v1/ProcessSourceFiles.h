#include <crow.h>

#include "../../Logger/Log.h"

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
    }
};