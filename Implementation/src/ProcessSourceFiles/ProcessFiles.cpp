#include "ProcessFiles.h"

#include <curl/curl.h>

#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "../Logger/Log.h"

namespace
{
// TODO: Implement API to test this....
// - Sequence, one api to post the URL and another to get if URL is valid
// - Maybe set as internal API.... just to test this
bool urlExists(const std::string& githubUrl)
{
#ifdef UNIT_TEST
    // Requires external dependencies that could cause noise into the unit tests
    return true;
#endif

    CURL* curl = curl_easy_init();
    if (!curl)
    {
        // TODO: Update it to log error.
        Logger::getInstance().log("[ProcessFiles][urlExists] Error with curl!!!");
        return false;
    }

    long http_code = 0;
    curl_easy_setopt(curl, CURLOPT_URL, githubUrl.c_str());  // Define the request URL
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);  // We only want headers - Don't donlaod body
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "crow-api-agent");  // Dfine user agent, required
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);           // Follow if redirect
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);                 // timeout

    CURLcode res = curl_easy_perform(curl);  // Execute the request
    if (res == CURLE_OK)
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,
                          &http_code);  // request the responsecode 200, 404 ...

    curl_easy_cleanup(curl);    // release used memory
    return (http_code == 200);  // Only return true if success
}

bool isUrlGitHubFolderOrFile(const std::string& githubUrl, const std::string& githubRegexpExpr)
{
    std::regex github_url_pattern(githubRegexpExpr);
    return std::regex_match(githubUrl, github_url_pattern);
}
}  // namespace

DownloadFiles::DownloadFiles(const std::string& originalURL) : m_originalURL(originalURL)
{
    // MUST call this constructor to instantiate this object.
    if (originalURL.empty())
    {
        throw std::invalid_argument("URL cannot be empty");
    }
}

std::string DownloadFiles::getOriginalURL()
{
    return m_originalURL;
}

// TODO: Implement API return based on input and this verification
bool DownloadFiles::isUrlFromGitHub()
{
    const std::string url = getOriginalURL();

    if (!isUrlGitHubFolderOrFile(url, githubRegexpExpr)) return false;
    if (!urlExists(url)) return false;

    return true;
}

bool DownloadFiles::isFolder()
{
    if (!isUrlFromGitHub())
    {
        Logger::getInstance().log("[DownloadFiles::isFolder] Not a valid path !!");
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
    if (!isUrlFromGitHub()) return;

    std::regex pattern(githubRegexpExpr);
    std::smatch match;

    std::cerr << "DownloadFiles::parseURL : " << m_originalURL << std::endl;

    if (std::regex_match(m_originalURL, match, pattern))
    {
        GitHubUrlInfo info;
        m_gitubUrlInfo.m_user = match[1].str();
        m_gitubUrlInfo.m_repo = match[2].str();
        m_gitubUrlInfo.m_branch = match[4].str();
        m_gitubUrlInfo.m_path = match[6].matched ? match[6].str() : "";
    }
}
