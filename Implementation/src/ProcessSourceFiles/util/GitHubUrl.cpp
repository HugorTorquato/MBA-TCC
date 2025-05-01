#include "GitHubUrl.h"

#include "../../Logger/Log.h"

GitHubUrlInfo::GitHubUrlInfo(const std::string& originalURL)
    : m_egexp(R"(https:\/\/github\.com\/([^\/]+)\/([^\/]+)\/(tree|blob)\/([^\/]+)(\/(.*))?)")
{
    parseURL(originalURL);
}

std::string GitHubUrlInfo::getRegexp() const
{
    return m_egexp;
}

bool GitHubUrlInfo::isValidUrl(const std::string& url) const
{
    std::regex github_url_pattern(m_egexp);
    return std::regex_match(url, github_url_pattern);
}

std::string GitHubUrlInfo::getBranch() const
{
    return m_branch;
}
std::string GitHubUrlInfo::getPath() const
{
    return m_path;
}
std::string GitHubUrlInfo::getRepo() const
{
    return m_repo;
}
std::string GitHubUrlInfo::getUser() const
{
    return m_user;
}

void GitHubUrlInfo::parseURL(const std::string& url)
{
    Logger::getInstance().log("url : " + url);

    if (url.empty() || !isValidUrl(url))
    {
        Logger::getInstance().log("[GitHubUrlInfo::parseURL] Error with URL!!! URL : " + url);
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
