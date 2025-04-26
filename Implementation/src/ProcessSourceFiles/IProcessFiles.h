#pragma once

#include <string>

#include "util/IHttpClient.h"

class IDownloadFiles
{
   public:
    virtual ~IDownloadFiles() = default;

    virtual std::string getOriginalURL() = 0;
    virtual std::string getBranch() = 0;
    virtual std::string getPath() = 0;
    virtual std::string getRepo() = 0;
    virtual std::string getUser() = 0;
    virtual std::string getEndpointToListFilesFromGitHub() = 0;

    virtual bool isUrlFromGitHub() = 0;
    virtual bool isValidUrl() = 0;
    virtual bool isFolder() = 0;

    virtual void parseURL() = 0;
};