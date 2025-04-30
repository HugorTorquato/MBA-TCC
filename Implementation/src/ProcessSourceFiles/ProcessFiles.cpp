#include "ProcessFiles.h"

#include <regex>
#include <stdexcept>
#include <string>

#include "../Logger/Log.h"
#include "FolderGraph.h"
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

json parseGitHubResponse(const std::string& response)
{
    auto parsed = json::parse(response);
    if (!parsed.is_array()) throw std::invalid_argument("GitHub response must be an array.");
    return parsed;
}
}  // namespace

DownloadFiles::DownloadFiles(const std::string& originalURL,
                             std::unique_ptr<IHttpClient> httpClient)
    : m_originalURL(originalURL),
      m_httpClient(std::move(httpClient)),
      m_folderGraph(FolderGraph(std::make_shared<ItemInFolder>("root", "dir")))
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

std::string DownloadFiles::getOriginalURL() const
{
    return m_originalURL;
}

// TODO: Implement API return based on input and this verification
bool DownloadFiles::isUrlFromGitHub()
{
    return isUrlFromGitHub(m_originalURL);
}

bool DownloadFiles::isUrlFromGitHub(const std::string& url)
{
    Logger::getInstance().log("url : " + url);
    Logger::getInstance().log("H1");
    if (url.empty()) return false;
    Logger::getInstance().log("H2");
    if (!isUrlGitHubFolderOrFile(
            url, m_githubRegexpExpr))  // Tem um Bug Aqui, if oher URL than the original one... it
                                       // fails... it's not generic
                                       // if (!isUrlGitHubFolderOrFile(url, m_githubRegexpExpr) ||
                                       //     !isUrlGitHubFolderOrFile(url, m_githubAPIRegexpExpr))
        return false;
    Logger::getInstance().log("H3");
    // if (!isValidUrl()) return false; ; Redundant, already checked in the getResponseFronUrl()

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

std::string DownloadFiles::getgithubRegexpExpr(RegexpTarget target) const
{
    if (target == RegexpTarget::GITHUB_API) return m_githubAPIRegexpExpr;
    // else if (target == RegexpTarget::GITHUB)
    return m_githubRegexpExpr;
}
std::string DownloadFiles::getBranch() const
{
    return m_gitubUrlInfo.m_branch;
}
std::string DownloadFiles::getPath() const
{
    return m_gitubUrlInfo.m_path;
}
std::string DownloadFiles::getRepo() const
{
    return m_gitubUrlInfo.m_repo;
}
std::string DownloadFiles::getUser() const
{
    return m_gitubUrlInfo.m_user;
}

FolderGraph DownloadFiles::getFolderGraph() const
{
    return m_folderGraph;
}

void DownloadFiles::parseURL(const std::string& url)
{
    // if (!isUrlFromGitHub(url))
    if (!isUrlFromGitHub())
    {
        Logger::getInstance().log("[DownloadFiles::parseURL] Error with URL!!! URL : " + url);
        return;
    }

    std::regex pattern(m_githubRegexpExpr);
    std::smatch match;

    if (std::regex_match(url, match, pattern))
    {
        GitHubUrlInfo info;
        m_gitubUrlInfo.m_user = match[1].str();
        m_gitubUrlInfo.m_repo = match[2].str();
        m_gitubUrlInfo.m_branch = match[4].str();
        m_gitubUrlInfo.m_path = match[6].matched ? match[6].str() : "";
    }
}

std::string DownloadFiles::getEndpointToListFilesFromGitHub(const std::string& url)
{
    parseURL(url);
    return "https://api.github.com/repos/" + m_gitubUrlInfo.m_user + "/" + m_gitubUrlInfo.m_repo +
           "/contents/" + m_gitubUrlInfo.m_path + "?ref=" + m_gitubUrlInfo.m_branch;
}

std::string DownloadFiles::listGitHubContentFromURL(const std::optional<std::string>& url)
{
    std::string response;
    std::string definedUrl = url ? *url : m_originalURL;

    const std::string endpointToListFiles = getEndpointToListFilesFromGitHub(definedUrl);

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
        return response;
    }

    if (!m_httpClient)
    {
        Logger::getInstance().log(
            "[DownloadFiles::listGitHubContentFromURL] Error with HTTP Client");
        return response;
    }
    if (!m_httpClient->getResponseFronUrl(endpointToListFiles, response, writeToString)) return "";
    // Logger::getInstance().log(response);
    return response;
}

void DownloadFiles::callRecursiveDoenloadMethod(const std::optional<std::string>& url,
                                                const std::shared_ptr<ItemInFolder>& parent)
{
    if (auto listedFilesFromGitHub = listGitHubContentFromURL(url); !listedFilesFromGitHub.empty())
    {
        json parsed = parseGitHubResponse(listedFilesFromGitHub);
        recursivelyDownloadFilesPopulatingGraph(parsed, parent);
    }
}

void DownloadFiles::recursivelyDownloadFilesPopulatingGraph(
    const json& parsed, const std::shared_ptr<ItemInFolder>& parent)
{
    if (!parsed.is_array())
        throw std::invalid_argument(
            "[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] Error Response is not an "
            "array!");

    for (const auto& item : parsed)
    {
        std::shared_ptr<ItemInFolder> child =
            std::make_shared<ItemInFolder>(item.value("name", ""), item.value("type", ""));

        if (child->getType() == ItemEnumType::UNKNOWN)
        {
            Logger::getInstance().log(
                "[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] Invalid child, no type "
                "defined");
            return;
        }

        Logger::getInstance().log("Name1: " + child->getName());  // remove

        if (child->getType() == ItemEnumType::SOURCEFILE)
        {
            // // try to download
            // try {
            //     // if (!downloadUrl.empty())
            //     // {
            //     //     m_httpClient->downloadFile(downloadUrl, item.value("name", ""),
            //     writeToString);
            //     // }
            // } catch (declaration) {

            // }
            m_folderGraph.addEdge(parent, child);
            Logger::getInstance().log("Name2: " + child->getName());
        }
        else if (child->getType() == ItemEnumType::DIR)
        {
            const std::string folderUrl = item.value("url", "");

            if (folderUrl.empty() || !isUrlFromGitHub())
            {
                Logger::getInstance().log(
                    "[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] Invalid folder URL, "
                    "folder " +
                    child->getName() + " will not be included in the folder graph : " + folderUrl);
                continue;
            }

            m_folderGraph.addEdge(parent, child);
            Logger::getInstance().log("Name3: " + child->getName());

            callRecursiveDoenloadMethod(folderUrl, child);  // child passa a ser o parent

            // if (auto listedFilesFromGitHub = listGitHubContentFromURL(folderUrl);
            //     !listedFilesFromGitHub.empty())
            // {
            //     json parsedChild = parseGitHubResponse(listedFilesFromGitHub);

            //     // recursivelyDownloadFilesPopulatingGraph(parsedChild, child); //child passa a
            //     ser o parent
            // }
            // Create temp local folder
        }

        // std::string name = item.value("name", "");
        // Logger::getInstance().log("Name: " + name);
    }

    // must have a stop condition
}

bool DownloadFiles::downloadURLContentIntoTempFolder()
{
    try
    {
        callRecursiveDoenloadMethod(std::nullopt, m_folderGraph.getRoot());
    }
    catch (const std::exception& e)
    {
        const std::string errorMessage =
            "[DownloadFiles::downloadURLContentIntoTempFolder] Error with JSON parsing: " +
            std::string(e.what());
        Logger::getInstance().log(errorMessage);
        throw std::runtime_error(errorMessage);
    }

    return true;
}
