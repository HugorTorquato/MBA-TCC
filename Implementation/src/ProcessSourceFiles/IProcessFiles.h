#pragma once

#include <string>

class IDownloadFiles
{
   public:
    virtual ~IDownloadFiles() = default;

    virtual std::string getOriginalURL() = 0;
    virtual bool isUrlFromGitHub() = 0;
};