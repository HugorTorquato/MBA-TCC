#include "GitHubUrlAPI.h"

#include "../../Logger/Log.h"

GitHubAPIUrlInfo::GitHubAPIUrlInfo(const std::string& originalURL)
    : m_egexp(
          R"(https:\/\/api\.github\.com\/repos\/([^\/]+)\/([^\/]+)\/contents\/(.*?)(?:\?ref=(.*))?)")
{
    parseURL(originalURL);
}

std::string GitHubAPIUrlInfo::getRegexp() const
{
    return m_egexp;
}

bool GitHubAPIUrlInfo::isValidUrl(const std::string& url) const
{
    std::regex github_url_pattern(m_egexp);
    return std::regex_match(url, github_url_pattern);
}

std::string GitHubAPIUrlInfo::getBranch() const
{
    return m_branch;
}
std::string GitHubAPIUrlInfo::getPath() const
{
    return m_path;
}
std::string GitHubAPIUrlInfo::getRepo() const
{
    return m_repo;
}
std::string GitHubAPIUrlInfo::getUser() const
{
    return m_user;
}

void GitHubAPIUrlInfo::parseURL(const std::string& url)
{
    Logger::getInstance().log("url : " + url);
    if (url.empty() || !isValidUrl(url))
    {
        Logger::getInstance().log("[GitHubAPIUrlInfo::parseURL] Error with URL!!! URL : " + url);
        return;
    }

    std::regex pattern(getRegexp());
    std::smatch match;

    if (std::regex_match(url, match, pattern))
    {
        m_user = match[1].str();
        m_repo = match[2].str();
        m_branch = match[4].str();
        m_path = match[6].matched ? match[6].str() : "";
    }
}