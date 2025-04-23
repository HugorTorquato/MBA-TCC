#pragma once

#include <string>

#include "IProcessFiles.h"

class DownloadFiles : public IDownloadFiles
{
   private:
    DownloadFiles() = delete;

   public:
    explicit DownloadFiles(const std::string& originalURL);

    std::string getOriginalURL() override;

    bool isUrlFromGitHub() override;

   private:
    std::string m_originalURL;
};