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

void validateRecursivelyDownloadFilesPopulatingGraphEntryParameters(
    const json& parsed, const std::shared_ptr<ItemInFolder>& parent)
{
    Logger::getInstance().log(
        "[DownloadFiles::validateRecursivelyDownloadFilesPopulatingGraphEntryParameters]");
    if (!parsed.is_array())
    {
        std::string errorMessage =
            "[DownloadFiles::validateRecursivelyDownloadFilesPopulatingGraphEntryParameters] Error "
            "Response is not an "
            "array! PrsedJson is not an array!";
        Logger::getInstance().log(errorMessage);
        throw std::invalid_argument(errorMessage);
    }

    if (!parent)
    {
        std::string errorMessage =
            "[DownloadFiles::validateRecursivelyDownloadFilesPopulatingGraphEntryParameters] Error "
            "Response is not an "
            "array! Parent pointer is not valid";
        Logger::getInstance().log(errorMessage);
        throw std::invalid_argument(errorMessage);
    }
}

// TODO: Make it more generic, becauase can be other types for other languages
bool isCppSourceFile(const std::string& fileName)
{
    Logger::getInstance().log("[DownloadFiles::isCppSourceFile] fileName: " + fileName);
    return fileName.find(".cpp") != std::string::npos || fileName.find(".h") != std::string::npos ||
           fileName.find(".hpp") != std::string::npos;
}

std::shared_ptr<ItemInFolder> instantiateChidFromParsedJsonItem(const json& item)
{
    Logger::getInstance().log("[DownloadFiles::instantiateChidFromParsedJsonItem]");

    const std::string name = item.value("name", "");
    const std::string pathStr = item.value("path", "");
    const unsigned int sizeInt = item.value("size", 0);
    const std::string urlStr = item.value("url", "");
    const std::string html_urlStr = item.value("html_url", "");
    // TODO: Maybe it's better to use this instead of url
    const std::string git_urlStr = item.value("git_url", "");
    const std::string download_urlStr = item.value("download_url", "");
    const std::string typeStr = item.value("type", "");

    return std::make_shared<ItemInFolder>(name, pathStr, sizeInt, urlStr, html_urlStr, git_urlStr,
                                          download_urlStr, typeStr);
}

json convertVectorWithNodeNameAndPath(const FolderGraph& folderGraph)
{
    Logger::getInstance().log("[ProcessFiles][convertVectorWithNodeNameAndPath] root path: " +
                              folderGraph.getRoot()->getName());

    auto result = folderGraph.dfsToJson(folderGraph.getRoot(), PropertySelector::Path);
    json jsonResult = json::array();

    for (const auto& item : result)
    {
        json jsonItem;
        jsonItem["name"] = item.first;
        jsonItem["path"] = std::get<std::filesystem::path>(item.second);
        Logger::getInstance().log(
            "[convertVectorWithNodeNameAndPath] name: " + item.first +
            " path: " + static_cast<std::string>(std::get<std::filesystem::path>(item.second)));
        jsonResult.push_back(jsonItem);
    }

    return jsonResult;
}
}  // namespace

DownloadFiles::DownloadFiles(const std::string& originalURL,
                             std::unique_ptr<IHttpClient> httpClient)
    : m_originalURL(originalURL),
      m_httpClient(std::move(httpClient)),
      m_folderGraph(
          FolderGraph(std::make_shared<ItemInFolder>("root", "", 0, "", "", "", "", "dir")))
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

std::string DownloadFiles::getTempFolder() const
{
    return m_tempFolder;
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
    if (urlInfo->isApi()) return url;
    return "https://api.github.com/repos/" + urlInfo->getUser() + "/" + urlInfo->getRepo() +
           "/contents/" + urlInfo->getPath() + "?ref=" + urlInfo->getBranch();
}

std::string DownloadFiles::listGitHubContentFromURL(const std::optional<std::string>& url)
{
    std::string response;
    std::string definedUrl = url ? *url : "";

    Logger::getInstance().log("[ProcessFiles][listGitHubContentFromURL] definedUrl: " + definedUrl);

    const std::string endpointToListFiles = getEndpointToListFilesFromGitHub(definedUrl);

    Logger::getInstance().log("[ProcessFiles][listGitHubContentFromURL] endpointToListFiles: " +
                              endpointToListFiles);

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
    Logger::getInstance().log("[DownloadFiles::callRecursiveDoenloadMethod] url: " +
                              (url ? *url : "") + " parent: " + (parent ? parent->getName() : ""));
    if (auto listedFilesFromGitHub = listGitHubContentFromURL(url); !listedFilesFromGitHub.empty())
    {
        json parsed = parseGitHubResponse(listedFilesFromGitHub);
        recursivelyDownloadFilesPopulatingGraph(parsed, parent);
    }
}

void DownloadFiles::recursivelyDownloadFilesPopulatingGraph(
    const json& parsed, const std::shared_ptr<ItemInFolder>& parent)
{
    Logger::getInstance().log("[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] parsed: " +
                              std::to_string(parsed.size()) +
                              " parent: " + (parent ? parent->getName() : ""));
    validateRecursivelyDownloadFilesPopulatingGraphEntryParameters(parsed, parent);

    for (const auto& item : parsed)
    {
        // const std::string name = item.value("name", "");
        // const std::string typeStr = item.value("type", "");
        // std::shared_ptr<ItemInFolder> child = std::make_shared<ItemInFolder>(name, typeStr);
        std::shared_ptr<ItemInFolder> child = instantiateChidFromParsedJsonItem(item);
        Logger::getInstance().log("Processing : " + child->getName());

        switch (child->getType())
        {
            case SOURCEFILE:
            {
                try
                {
                    const std::string downloadUrl = item.value("download_url", "");
                    const std::string path = item.value("path", "");

                    if (!downloadUrl.empty() && isCppSourceFile(child->getName()))
                    {
                        m_httpClient->downloadFile(downloadUrl, m_tempFolder + path, writeToString);
                        m_folderGraph.addEdge(parent, child);
                    }
                }
                catch (const std::exception& e)
                {
                    Logger::getInstance().log(
                        "[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] Error "
                        "download file: " +
                        std::string(e.what()));
                }

                Logger::getInstance().log("SOURCEFILE Name: " + child->getName());
                break;
            }
            case DIR:
            {
                // No need to create the folders because wehn downloading the files, the folders are
                // created

                const std::string folderUrl = item.value("url", "");

                if (!RepoURLFactory::isFromGtHub(folderUrl))
                {
                    Logger::getInstance().log(
                        "[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] Invalid folder "
                        "URL, folder " +
                        child->getName() +
                        " will not be included in the folder graph : " + folderUrl);
                    continue;
                }

                m_folderGraph.addEdge(parent, child);
                Logger::getInstance().log("DIR Name: " + child->getName());

                callRecursiveDoenloadMethod(folderUrl, child);  // bhid becomes parent
                break;
            }
            case UNKNOWN:
            default:
            {
                Logger::getInstance().log(
                    "[DownloadFiles::recursivelyDownloadFilesPopulatingGraph] Default child, no "
                    "type defined");
                break;
            }
        }
    }
}

json DownloadFiles::downloadURLContentIntoTempFolder()
{
    Logger::getInstance().log("[DownloadFiles::downloadURLContentIntoTempFolder] m_originalURL: " +
                              m_originalURL);

    json response;

    if (m_originalURL.empty())
    {
        Logger::getInstance().log(
            "[DownloadFiles::downloadURLContentIntoTempFolder] Empty initial URL");
        return response;
    }

    try
    {
        callRecursiveDoenloadMethod(m_originalURL, m_folderGraph.getRoot());
        response = convertVectorWithNodeNameAndPath(m_folderGraph);
    }
    catch (const std::exception& e)
    {
        const std::string errorMessage =
            "[DownloadFiles::downloadURLContentIntoTempFolder] Error with JSON parsing: " +
            std::string(e.what());
        Logger::getInstance().log(errorMessage);
        throw std::runtime_error(errorMessage);
    }

    // Traverse the graph to return the list of downloaded files

    return response;
}

// TODO: iF there is string representing something it's wring... create a class for that
