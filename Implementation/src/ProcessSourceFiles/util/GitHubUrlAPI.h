#pragma once

#include <string>

#include "IRepoURL.h"

class GitHubAPIUrlInfo : public IRepoURL
{
   public:
    GitHubAPIUrlInfo(const std::string& originalURL);

    bool isValidUrl(const std::string& url) const override;

    std::string getBranch() const override;
    std::string getPath() const override;
    std::string getRepo() const override;
    std::string getUser() const override;
    std::string getRegexp() const override;

    void parseURL(const std::string& url) override;
    bool isFromGtHub() const override;
    bool isFromGtHub(const std::string& url) const override;
    bool isFolder(const std::string& url) const override;

   private:
    std::string m_branch;
    std::string m_path;
    std::string m_repo;
    std::string m_user;
    std::string m_egexp;
    std::string m_url;
};