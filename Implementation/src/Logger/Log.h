#pragma once

#include <string>

// TODO: 
//     - Implement logic to limit the amount of memory of the logs. Like 5 files of 100 Mb.
//     - Add log levels and types of logs for different sections
//     - Make it thread safe ( when needed )
//     - Implement Unit Tests for this class
class Logger
{

    private:
        Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    public:
        static Logger& getInstance();
        ~Logger() = default; // Destructor in the public section?

        bool getEnabledLogs() const;
        void setEnabledLogs(const bool enabled);

        void log(const std::string& msg);

    private:
        bool m_enabledLogs = true;
};