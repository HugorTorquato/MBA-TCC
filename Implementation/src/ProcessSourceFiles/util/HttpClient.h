#pragma once

#include <curl/curl.h>

#include "IHttpClient.h"

class CurlHttpClient : public IHttpClient
{
   public:
    CurlHttpClient();
    ~CurlHttpClient();

    // CURL* getHttpClient() const;
    bool getResponseFronUrl(
        const std::string& url, std::string& response,
        std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback) override;

    void downloadFile(
        const std::string& url, const std::string& outputPath,
        std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback) override;

   private:
    CURL* m_curl;
};
