#include <crow.h>

#include "Logger/Log.h"
#include "api/v1/GeneralInfo.h"
#include "api/v1/ProcessSourceFiles.h"

int main()
{
    crow::SimpleApp app;  // Creates the Crow application instance.
    GeneralInfo _generalInfo;
    ProcessSourceFiles _processSourceFiles;
    Logger::getInstance().log("Starting main execution");

    // TODO:
    //  - Why not put everything static here, for the initialiation?
    _generalInfo.setup_GeneralInfo_Routes(app);
    _processSourceFiles.setup_ProcessSourceFiles_Routes(app);

    app.port(8080).multithreaded().run();  // Run the API server on port 8080
}