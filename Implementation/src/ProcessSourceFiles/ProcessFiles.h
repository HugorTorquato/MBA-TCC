#pragma once

#include <curl/curl.h>

#include <string>

#include "IProcessFiles.h"

struct GitHubUrlInfo
{
    std::string m_branch;
    std::string m_path;
    std::string m_repo;
    std::string m_user;
};

class CurlRAII
{
   public:
    CurlRAII() : curl(curl_easy_init()) {}
    ~CurlRAII()
    {
        if (curl)
        {
            curl_easy_cleanup(curl);
        }
    }
    CURL* get() const
    {
        return curl;
    }

   private:
    CURL* curl;
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