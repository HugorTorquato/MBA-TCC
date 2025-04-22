#pragma once

#include <string>

class DownloadFiles
{
   private:
    DownloadFiles() = delete;

   public:
    explicit DownloadFiles(const std::string& originalURL);

    std::string getOriginalURL();

   private:
    std::string m_originalURL;
};