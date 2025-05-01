#include "RepoURLFactory.h"

#include "../Logger/Log.h"
#include "util/GitHubUrl.h"
#include "util/GitHubUrlAPI.h"

std::unique_ptr<IRepoURL> RepoURLFactory::createRepoURL(const std::string& url)
{
    Logger::getInstance().log("[RepoURLFactory::createRepoURL]Creating RepoURL for: " + url);
    if (url.find("api.github.com") != std::string::npos)
    {
        return std::make_unique<GitHubAPIUrlInfo>(url);
    }
    else if (url.find("github.com") != std::string::npos)
    {
        return std::make_unique<GitHubUrlInfo>(url);
    }
    else
    {
        throw std::invalid_argument("Unsupported URL");
    }
}

bool RepoURLFactory::isFromGtHub(const std::string& url){
    Logger::getInstance().log("[RepoURLFactory::isFromGtHub] Evaluating : " + url);
    if(url.empty())
        return false;

    if (url.find("api.github.com") != std::string::npos)
    {
        auto repoURL = std::make_unique<GitHubAPIUrlInfo>(url);
        return repoURL->isFromGtHub();
    }
    else if (url.find("github.com") != std::string::npos)
    {
        auto repoURL = std::make_unique<GitHubUrlInfo>(url);
        return repoURL->isFromGtHub();
    }
    else
    {
        throw std::invalid_argument("Unsupported URL");
    }
}