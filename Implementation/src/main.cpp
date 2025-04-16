#include <crow.h>

#include "../includes/api/v1/GeneralInfo.h"
#include "Logger/Log.h"

int main()
{
    crow::SimpleApp app;  // Creates the Crow application instance.
    GeneralInfo _generalInfo;
    Logger::getInstance().log("Starting main execution");

    _generalInfo.setup_GeneralInfo_Routes(app);

    app.port(8080).multithreaded().run();  // Run the API server on port 8080
}