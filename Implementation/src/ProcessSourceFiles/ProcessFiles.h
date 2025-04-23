#pragma once

#include <string>

#include "IProcessFiles.h"

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
    explicit DownloadFiles(const std::string& originalURL);

    std::string getOriginalURL() override;
    std::string getBranch() override;
    std::string getPath() override;
    std::string getRepo() override;
    std::string getUser() override;

    bool isUrlFromGitHub() override;
    bool isFolder() override;

    void parseURL() override;

   private:
    std::string m_originalURL;
    GitHubUrlInfo m_gitubUrlInfo;

    const std::string githubRegexpExpr =
        R"(https:\/\/github\.com\/([^\/]+)\/([^\/]+)\/(tree|blob)\/([^\/]+)(\/(.*))?)";
};