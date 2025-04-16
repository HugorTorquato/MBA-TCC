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
                    auto body = crow::json::load(req.body);

                    if (!body) return crow::response(400, "Invalid JSON");

                    std::string git_url = body["url"].s();

                    return crow::response("Received GitHub URL: " + git_url);
                });
    }
};