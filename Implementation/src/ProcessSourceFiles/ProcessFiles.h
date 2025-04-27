#pragma once

#include <memory>
#include <string>

#include "IProcessFiles.h"
#include "util/IHttpClient.h"

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

    std::string getOriginalURL() override;
    std::string getBranch() override;
    std::string getPath() override;
    std::string getRepo() override;
    std::string getUser() override;
    std::string getEndpointToListFilesFromGitHub() override;

    bool isUrlFromGitHub() override;
    bool isValidUrl() override;
    bool isFolder() override;

    void parseURL() override;

    std::string listGitHubContentFromURL() override;
    bool downloadURLContentIntoTempFolder() override;

   private:
    std::string m_originalURL;
    GitHubUrlInfo m_gitubUrlInfo;
    // IHttpClient& m_httpClient;
    std::unique_ptr<IHttpClient> m_httpClient;

    const std::string githubRegexpExpr =
        R"(https:\/\/github\.com\/([^\/]+)\/([^\/]+)\/(tree|blob)\/([^\/]+)(\/(.*))?)";
};