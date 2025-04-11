#include <crow.h>

class GeneralInfo
{
    public:
        void setup_GeneralInfo_Routes(crow::SimpleApp& app){
            setup_API_Status_route(app);
        }

    private:
        void setup_API_Status_route(crow::SimpleApp& app){
            CROW_ROUTE(app, "/status").methods(crow::HTTPMethod::GET) 
            // Declare a new route (endpoint) that will listen to GET requests on "/status". 
            // This route only accepts GET requests
            ([](){
                crow::json::wvalue result; // A Crow JSON response builder. You use it like a dictionary in Python.

                result["status"] = "API is running";
                return crow::response(result);
            });
        }
};