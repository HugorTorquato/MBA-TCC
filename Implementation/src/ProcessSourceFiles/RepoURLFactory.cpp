#include "RepoURLFactory.h"

#include "../Logger/Log.h"
#include "util/GitHubUrl.h"
#include "util/GitHubUrlAPI.h"

std::unique_ptr<IRepoURL> RepoURLFactory::createRepoURL(const std::string& url)
{
    Logger::getInstance().log("Creating RepoURL for: " + url);
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