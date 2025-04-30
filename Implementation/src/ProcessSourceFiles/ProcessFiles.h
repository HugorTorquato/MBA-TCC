#pragma once

#include <memory>
#include <string>

#include "IProcessFiles.h"
#include "util/IHttpClient.h"

enum RegexpTarget
{
    GITHUB_API,
    GITHUB
};

struct GitHubUrlInfo
{
    std::string m_branch;
    std::string m_path;
    std::string m_repo;
    std::string m_user;
};

class DownloadFiles : public IDownloadFiles
{
   private:
    DownloadFiles() = delete;

   public:
    explicit DownloadFiles(const std::string& originalURL, std::unique_ptr<IHttpClient> httpClient);

    std::string getOriginalURL() const override;
    std::string getBranch() const override;
    std::string getPath() const override;
    std::string getRepo() const override;
    std::string getUser() const override;
    FolderGraph getFolderGraph() const override;
    std::string getEndpointToListFilesFromGitHub(const std::string& url) override;

    bool isUrlFromGitHub() override;
    bool isUrlFromGitHub(const std::string& url) override;
    bool isValidUrl() override;
    bool isFolder() override;

    void parseURL(const std::string& url) override;

    std::string listGitHubContentFromURL(const std::optional<std::string>& url) override;
    void recursivelyDownloadFilesPopulatingGraph(
        const json& parsed, const std::shared_ptr<ItemInFolder>& parent) override;
    bool downloadURLContentIntoTempFolder() override;

    void callRecursiveDoenloadMethod(const std::optional<std::string>& url,
                                     const std::shared_ptr<ItemInFolder>& parent);
    std::string getgithubRegexpExpr(RegexpTarget target) const;

   private:
    std::string m_originalURL;
    GitHubUrlInfo m_gitubUrlInfo;
    FolderGraph m_folderGraph;
    std::unique_ptr<IHttpClient> m_httpClient;

    const std::string m_githubAPIRegexpExpr =
        R"(https:\/\/api\.github\.com\/repos\/([^\/]+)\/([^\/]+)\/contents\/(.*)\?ref=([^\/]+))";
    const std::string m_githubRegexpExpr =
        R"(https:\/\/github\.com\/([^\/]+)\/([^\/]+)\/(tree|blob)\/([^\/]+)(\/(.*))?)";
    // R"(https:\/\/github\.com\/([^\/]+)\/([^\/]+)\/(tree|blob)\/([^\/]+)(?:\/(.*))?)";
    // R"(https:\/\/(?:api\.github\.com\/repos\/([^\/]+)\/([^\/]+)\/contents\/(.*)\?ref=([^\/]+)|github\.com\/([^\/]+)\/([^\/]+)\/(tree|blob)\/([^\/]+)(?:\/(.*))?))";
};