#include "ProcessFiles.h"

#include <regex>
#include <stdexcept>
#include <string>

#include "../Logger/Log.h"
#include "util/IHttpClient.h"

namespace
{
// TODO: Implement API to test this....
// - Sequence, one api to post the URL and another to get if URL is valid
// - Maybe set as internal API.... just to test this
// - With the new wrapper i can unit test this passing the curl wrapper as a parameter to mock

bool isUrlGitHubFolderOrFile(const std::string& githubUrl, const std::string& githubRegexpExpr)
{
    std::regex github_url_pattern(githubRegexpExpr);
    return std::regex_match(githubUrl, github_url_pattern);
}

// Callback to store the response string ( Transform this to function header )
size_t writeToString(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool errorWithUrlInfoMember(const GitHubUrlInfo& gitubUrlInfo)
{
    return gitubUrlInfo.m_branch.empty() || gitubUrlInfo.m_path.empty() ||
           gitubUrlInfo.m_repo.empty() || gitubUrlInfo.m_user.empty();
}
}  // namespace

DownloadFiles::DownloadFiles(const std::string& originalURL,
                             std::unique_ptr<IHttpClient> httpClient)
    : m_originalURL(originalURL), m_httpClient(std::move(httpClient))
{
    // MUST call this constructor to instantiate this object.
    if (originalURL.empty())
    {
        throw std::invalid_argument("URL cannot be empty");
    }
}

bool DownloadFiles::isValidUrl()
{
    std::string response;
    if (!m_httpClient)
    {
        Logger::getInstance().log("[DownloadFiles::isValidUrl] Error with HTTP Client");
        return false;
    }
    return m_httpClient->getResponseFronUrl(m_originalURL, response);
}

std::string DownloadFiles::getOriginalURL()
{
    return m_originalURL;
}

// TODO: Implement API return based on input and this verification
bool DownloadFiles::isUrlFromGitHub()
{
    if (!isUrlGitHubFolderOrFile(m_originalURL, githubRegexpExpr)) return false;
    if (!isValidUrl()) return false;

    return true;
}

bool DownloadFiles::isFolder()
{
    if (!isUrlFromGitHub())
    {
        Logger::getInstance().log("[DownloadFiles::isFolder] Not a valid path !!!");
        return false;
    }
    std::regex github_url_pattern(R""(.*tree.*)"");
    return std::regex_match(m_originalURL, github_url_pattern);
}

std::string DownloadFiles::getBranch()
{
    return m_gitubUrlInfo.m_branch;
}
std::string DownloadFiles::getPath()
{
    return m_gitubUrlInfo.m_path;
}
std::string DownloadFiles::getRepo()
{
    return m_gitubUrlInfo.m_repo;
}
std::string DownloadFiles::getUser()
{
    return m_gitubUrlInfo.m_user;
}

void DownloadFiles::parseURL()
{
    if (!isUrlFromGitHub())
    {
        Logger::getInstance().log("[DownloadFiles::parseURL] Error with URL!!! URL : " +
                                  m_originalURL);
        return;
    }

    std::regex pattern(githubRegexpExpr);
    std::smatch match;

    if (std::regex_match(m_originalURL, match, pattern))
    {
        GitHubUrlInfo info;
        m_gitubUrlInfo.m_user = match[1].str();
        m_gitubUrlInfo.m_repo = match[2].str();
        m_gitubUrlInfo.m_branch = match[4].str();
        m_gitubUrlInfo.m_path = match[6].matched ? match[6].str() : "";
    }
}

std::string DownloadFiles::getEndpointToListFilesFromGitHub()
{
    return "https://api.github.com/repos/" + m_gitubUrlInfo.m_user + "/" + m_gitubUrlInfo.m_repo +
           "/contents/" + m_gitubUrlInfo.m_path + "?ref=" + m_gitubUrlInfo.m_branch;
}

std::string DownloadFiles::listGitHubContentFromURL()
{
    parseURL();
    const std::string endpointToListFiles = getEndpointToListFilesFromGitHub();
    if (endpointToListFiles.empty() || errorWithUrlInfoMember(m_gitubUrlInfo))
    {
        const std::string errorMessage =
            "[ProcessFiles][listGitHubContentFromURL] Error with endpoint!!! "
            " endpointToListFiles:  " +
            endpointToListFiles + " gitubUrlInfo.m_branch:" + m_gitubUrlInfo.m_branch +
            " gitubUrlInfo.m_path:" + m_gitubUrlInfo.m_path +
            " gitubUrlInfo.m_repo:" + m_gitubUrlInfo.m_repo +
            " gitubUrlInfo.m_user:" + m_gitubUrlInfo.m_user;
        Logger::getInstance().log(errorMessage);
        throw std::invalid_argument(errorMessage);
        return "";
    }

    std::string response;
    if (!m_httpClient)
    {
        Logger::getInstance().log(
            "[DownloadFiles::listGitHubContentFromURL] Error with HTTP Client");
        return response;
    }
    m_httpClient->getResponseFronUrl(endpointToListFiles, response, writeToString);
    return response;
}
