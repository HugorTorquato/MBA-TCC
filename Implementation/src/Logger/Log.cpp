#include "Log.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#define CERR_LOGS 1

Logger::Logger()
{
    // Truncate is cheaper than deleting and creating the file again
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

void Logger::log(const std::string& msg)
{
    // Get current time with milliseconds
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // Format time as [YYYY-MM-DD HH:MM:SS.mmm]
    std::ostringstream oss;
    oss << "[" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << "."
        << std::setfill('0') << std::setw(3) << ms.count() << "] " << msg;

    std::string logMsg = oss.str();

    if (CERR_LOGS) std::cerr << logMsg << std::endl;
    if (!m_enabledLogs) return;

    std::ofstream file("app.log", std::ios::app);  // Append mode
    file << logMsg << std::endl;
}
