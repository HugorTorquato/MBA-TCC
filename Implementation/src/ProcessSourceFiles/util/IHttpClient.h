#pragma once

#include <functional>
#include <optional>
#include <string>

class IHttpClient
{
   public:
    virtual ~IHttpClient() = default;

    // User can custom the callback function by simply pass a freefunction when calling this method.
    // Or use the default one.
    virtual bool getResponseFronUrl(
        const std::string& url, std::string& response,
        std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback = std::nullopt) = 0;

    virtual void downloadFile(
        const std::string& url, const std::string& outputPath,
        std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback) = 0;
};