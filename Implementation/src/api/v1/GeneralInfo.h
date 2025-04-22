#include <crow.h>

#include "../../Logger/Log.h"

class GeneralInfo
{
   public:
    void setup_GeneralInfo_Routes(crow::SimpleApp& app)
    {
        Logger::getInstance().log("Starting General Info Routes.");

        setup_API_Status_route(app);
    }

   private:
    void setup_API_Status_route(crow::SimpleApp& app)
    {
        CROW_ROUTE(app, "/api/v1/status")
            .methods(crow::HTTPMethod::GET)
            // Declare a new route (endpoint) that will listen to GET requests on "/status".
            // This route only accepts GET requests
            (
                []()
                {
                    Logger::getInstance().log("Accessing /api/v1/status route.");
                    crow::json::wvalue result;  // A Crow JSON response builder. You use it like a
                                                // dictionary in Python.

                    result["status"] = "API is running";
                    return crow::response(result);
                });
    }
};