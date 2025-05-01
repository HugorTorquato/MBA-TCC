#include "ProcessFiles.h"

#include <memory>
#include <regex>
#include <stdexcept>
#include <string>

#include "../Logger/Log.h"
#include "FolderGraph.h"
#include "RepoURLFactory.h"
#include "util/IHttpClient.h"
#include "util/IRepoURL.h"

namespace
{
// TODO: Implement API to test this....
// - Sequence, one api to post the URL and another to get if URL is valid
// - Maybe set as internal API.... just to test this
// - With the new wrapper i can unit test this passing the curl wrapper as a parameter to mock

// Callback to store the response string ( Transform this to function header )
size_t writeToString(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool errorWithUrlInfoMember(const IRepoURL& urlInfo)
{
    return urlInfo.getBranch().empty() || urlInfo.getPath().empty() || urlInfo.getRepo().empty() ||
           urlInfo.getUser().empty();
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

    m_urlInfo = RepoURLFactory::createRepoURL(originalURL);

    if (!m_urlInfo)
    {
        throw std::invalid_argument("Invalid URL");
    }
}

bool DownloadFiles::verifyIfValidEndpointByCallingIt()
{
    // Be vary carrefully when using it. It calls an api to see if it is valid. May generate
    // overhead and slowness
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

// bool DownloadFiles::isFolder()
// {
//     if (!isUrlFromGitHub())
//     {
//         Logger::getInstance().log("[DownloadFiles::isFolder] Not a valid path !!!");
//         return false;
//     }
//     std::regex github_url_pattern(R""(.*tree.*)"");
//     return std::regex_match(m_originalURL, github_url_pattern);
// }

// std::string DownloadFiles::getgithubRegexpExpr(RegexpTarget target) const
// {
//     if (target == RegexpTarget::GITHUB_API)
//         return m_githubAPIRegexpExpr;
//     else if (target == RegexpTarget::GITHUB)
//         return m_urlInfo->getRegexp();
// }

std::string DownloadFiles::getBranch() const
{
    return m_urlInfo->getBranch();
}
std::string DownloadFiles::getPath() const
{
    return m_urlInfo->getPath();
}
std::string DownloadFiles::getRepo() const
{
    return m_urlInfo->getRepo();
}
std::string DownloadFiles::getUser() const
{
    return m_urlInfo->getUser();
}

FolderGraph DownloadFiles::getFolderGraph() const
{
    return m_folderGraph;
}

IRepoURL* DownloadFiles::getUrlInfo() const
{
    return m_urlInfo.get();
}

std::string DownloadFiles::getEndpointToListFilesFromGitHub(const std::string& url)
{
    // Since i'm receiving an url here, i need to creae a new loal object to parse it correctly.
    auto urlInfo = RepoURLFactory::createRepoURL(url);
    return "https://api.github.com/repos/" + urlInfo->getUser() + "/" + urlInfo->getRepo() +
           "/contents/" + urlInfo->getPath() + "?ref=" + urlInfo->getBranch();
}

std::string DownloadFiles::listGitHubContentFromURL(const std::optional<std::string>& url)
{
    std::string response;
    std::string definedUrl = url ? *url : m_originalURL;

    const std::string endpointToListFiles = getEndpointToListFilesFromGitHub(definedUrl);

    if (endpointToListFiles.empty() || (m_urlInfo && errorWithUrlInfoMember(*m_urlInfo)))
    {
        const std::string errorMessage =
            "[ProcessFiles][listGitHubContentFromURL] Error with endpoint!!! "
            " endpointToListFiles:  " +
            endpointToListFiles + " gitubUrlInfo.m_branch:" + getBranch() +
            " gitubUrlInfo.m_path:" + getPath() + " gitubUrlInfo.m_repo:" + getRepo() +
            " gitubUrlInfo.m_user:" + getUser();
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

// TODO: No need to be in the class.. can be unnamedsace
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

        Logger::getInstance().log(
            "[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] Name: " +
            child->getName());  // remove

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

            // auto repoUrl = RepoURLFactory::createRepoURL(folderUrl);

            // if (repoUrl && !repoUrl->isFromGtHub())
            if (!RepoURLFactory::isFromGtHub(folderUrl))
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

// TODO: iF there is string representing something it's wring... create a class for that