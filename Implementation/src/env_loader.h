// env_loader.h
#pragma once
#include <cstdlib>
#include <fstream>
#include <string>

inline void loadDotEnv(const std::string& path = "/app/.env")
{
    std::ifstream envFile(path);
    std::string line;

    while (std::getline(envFile, line))
    {
        size_t pos = line.find('=');
        if (pos == std::string::npos) continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        setenv(key.c_str(), value.c_str(), 1);  // or _putenv_s on Windows
    }
}
