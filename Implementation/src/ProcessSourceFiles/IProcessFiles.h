#pragma once

#include <string>

#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json
#include "FolderGraph.h"
#include "util/IHttpClient.h"
#include "util/IRepoURL.h"

using json = nlohmann::json;

class IDownloadFiles
{
   public:
    virtual ~IDownloadFiles() = default;

    virtual std::string getOriginalURL() const = 0;
    virtual std::string getBranch() const = 0;
    virtual std::string getPath() const = 0;
    virtual std::string getRepo() const = 0;
    virtual std::string getUser() const = 0;
    virtual std::string getTempFolder() const = 0;
    virtual FolderGraph getFolderGraph() const = 0;
    virtual std::string getEndpointToListFilesFromGitHub(const std::string& url) = 0;
    virtual const IRepoURL* getUrlInfo() const = 0;

    virtual bool verifyIfValidEndpointByCallingIt() = 0;

    virtual std::string listGitHubContentFromURL(const std::optional<std::string>& url) = 0;
    virtual void recursivelyDownloadFilesPopulatingGraph(
        const json& parsed, const std::shared_ptr<ItemInFolder>& parent) = 0;
    virtual bool downloadURLContentIntoTempFolder() = 0;
};