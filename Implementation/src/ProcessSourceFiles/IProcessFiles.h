#pragma once

#include <string>

#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json
#include "FolderGraph.h"
#include "util/IHttpClient.h"

using json = nlohmann::json;

class IDownloadFiles
{
   public:
    virtual ~IDownloadFiles() = default;

    virtual std::string getOriginalURL() = 0;
    virtual std::string getBranch() = 0;
    virtual std::string getPath() = 0;
    virtual std::string getRepo() = 0;
    virtual std::string getUser() = 0;
    virtual std::string getEndpointToListFilesFromGitHub(const std::string& url) = 0;

    virtual bool isUrlFromGitHub() = 0;
    virtual bool isValidUrl() = 0;
    virtual bool isFolder() = 0;

    virtual void parseURL(const std::string& url) = 0;

    virtual std::string listGitHubContentFromURL(const std::optional<std::string>& url) = 0;
    virtual void recursivelyDownloadFilesPopulatingGraph(
        const json& parsed, const std::shared_ptr<ItemInFolder>& parent) = 0;
    virtual bool downloadURLContentIntoTempFolder() = 0;
};