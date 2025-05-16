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
    std::string getTempFolder() const override;
    FolderGraph getFolderGraph() const override;
    std::string getEndpointToListFilesFromGitHub(const std::string& url) override;
    IRepoURL* getUrlInfo() const override;

    bool verifyIfValidEndpointByCallingIt() override;

    std::string listGitHubContentFromURL(const std::optional<std::string>& url) override;
    void recursivelyDownloadFilesPopulatingGraph(
        const json& parsed, const std::shared_ptr<ItemInFolder>& parent) override;
    json downloadURLContentIntoTempFolder() override;

    void callRecursiveDoenloadMethod(const std::optional<std::string>& url,
                                     const std::shared_ptr<ItemInFolder>& parent);
    // std::string getgithubRegexpExpr(RegexpTarget target) const;

    void processChildNode(const json& item, const std::shared_ptr<ItemInFolder>& child,
                          const std::shared_ptr<ItemInFolder>& parent);
    void processSourceFile(const json& item, const std::shared_ptr<ItemInFolder>& child,
                           const std::shared_ptr<ItemInFolder>& parent);
    void processDirectory(const json& item, const std::shared_ptr<ItemInFolder>& child,
                          const std::shared_ptr<ItemInFolder>& parent);

   private:
    std::string m_originalURL;
    std::unique_ptr<IRepoURL> m_urlInfo;
    FolderGraph m_folderGraph;
    std::unique_ptr<IHttpClient> m_httpClient;

    const std::string m_tempFolder = "/app/temp/";
};