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
}  // namespace

DownloadFiles::DownloadFiles(const std::string& originalURL, IHttpClient& httpClient)
    : m_originalURL(originalURL), m_httpClient(httpClient)
{
    // MUST call this constructor to instantiate this object.
    if (originalURL.empty())
    {
        throw std::invalid_argument("URL cannot be empty");
    }
}

bool DownloadFiles::isValidUrl()
{
#ifdef UNIT_TEST
    // Requires external dependencies that could cause noise into the unit tests
    return true;
#endif

    std::string response;

    return m_httpClient.getResponseFronUrl(m_originalURL, response);
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
    if (!isValidUrl()) return false;

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

// based on the parsed URL, i need to create the github request to list folders and files

namespace
{
// Step 1: Callback to store the response string ( Transform this to function header )
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

// TODO: Better way to implement this curl requests
std::string DownloadFiles::listGitHubContentFromURL()
{
    const std::string endpointToListFiles = getEndpointToListFilesFromGitHub();
    if (endpointToListFiles.empty() || errorWithUrlInfoMember(m_gitubUrlInfo))
    {
        Logger::getInstance().log(
            "[ProcessFiles][listGitHubContentFromURL] Error with endpoint!!! "
            " endpointToListFiles:  " +
            endpointToListFiles + " gitubUrlInfo.m_branch:" + m_gitubUrlInfo.m_branch +
            " gitubUrlInfo.m_path:" + m_gitubUrlInfo.m_path + " gitubUrlInfo.m_repo:" +
            m_gitubUrlInfo.m_repo + " gitubUrlInfo.m_user:" + m_gitubUrlInfo.m_user);
        throw std::invalid_argument("[ProcessFiles][listGitHubContentFromURL] URL cannot be empty");
        return "";
    }

    return "";

    // CurlRAII curlWrapper;
    // CURL* curl = curlWrapper.get();
    // if (!curl)
    // {
    //     // TODO: Update it to log error.
    //     Logger::getInstance().log("[ProcessFiles][urlExists] Error with curl!!!");
    //     return;
    // }

    // long http_code = 0;
    // std::string response_data;

    // curl_easy_setopt(curl, CURLOPT_URL, endpointToListFiles);  // Define the request URL
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString); // Callback
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);    // Where to write
    // curl_easy_setopt(curl, CURLOPT_USERAGENT, "crow-api-agent");
    // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);           // Follow redirects
    // curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);                 // Timeout in 10s

    // CURLcode res = curl_easy_perform(curl);  // Execute the request
    // if (res != CURLE_OK)
    // {
    //     Logger::getInstance().log("[ProcessFiles][listGitHubContentFromURL] Error with curl!!!
    //     %s",
    //                                 curl_easy_strerror(res).c_str());
    //     return;
    // }
}
