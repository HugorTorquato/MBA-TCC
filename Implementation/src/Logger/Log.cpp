#include "Log.h"

#include <iostream>
#include <fstream>
// #include <string>

Logger::Logger() {
    //Truncate is cheaper than deleting and creating the file again
    std::ofstream file("../../build/app.log", std::ios::trunc);
    file << "Log start\n";
};

// The keyword static here is incorrect in the .cpp file — static inside
//  a source file makes the function have internal linkage, so it's invisible 
//  to the linker when used elsewhere.
Logger& Logger::getInstance()
{
    // Static local variable -> object created in the first time it passes here
    // and on all other calls, the initialization will be skipped.
    static Logger instance;
    return instance;
}


bool Logger::getEnabledLogs() const
{
    return m_enabledLogs;
}
void Logger::setEnabledLogs(const bool enabled)
{
    m_enabledLogs = enabled;
}

void Logger::log(const std::string& msg) {

    if(!m_enabledLogs) return;

    std::ofstream file("app.log", std::ios::app); // Append mode
    file << msg << std::endl;
}

