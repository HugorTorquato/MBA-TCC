#include "HttpClient.h"

#include <curl/curl.h>
#include <curl/easy.h>

#include <stdexcept>
#include <string>

#include "../../Logger/Log.h"

namespace
{
size_t writeToStringCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    // contents	     -> Is the data received from the HTTP response (a chunk of it).
    // size * nmemb	 -> Gives the actual size of that chunk.
    // userp	     -> Is the pointer to your std::string (you gave it when configuring curl).
    // static_cast<std::string*>(userp)	 -> You cast it back to a real std::string*.
    // append	     -> You append the received data to the string.
    // return totalSize	 -> You return how many bytes you processed (curl expects this).
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}
}  // namespace

CurlHttpClient::CurlHttpClient() : m_curl(curl_easy_init())
{
    if (!m_curl)
    {
        Logger::getInstance().log("[CurlHttpClient] Failed to initialize CURL");
        throw std::runtime_error("Failed to initialize CURL");
    }
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CurlHttpClient::~CurlHttpClient()
{
    if (m_curl)
    {
        curl_easy_cleanup(m_curl);
    }
}

bool CurlHttpClient::getResponseFronUrl(
    const std::string& url, std::string& response,
    std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback)
{
    Logger::getInstance().log("[CurlHttpClient::getResponseFronUrl] Fetching URL: " + url);

    if (!m_curl) return false;

    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    if (writeCallback.has_value())
    {
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback.value());
    }
    else
    {
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeToStringCallback);
    }
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "Crow-GitHub-Agent");
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 20L);

    CURLcode res = curl_easy_perform(m_curl);
    bool success = (res == CURLE_OK);

    if (!success)
    {
        Logger::getInstance().log(std::string(
            "[CurlHttpClient::getResponseFronUrl] Error with curl: %s", curl_easy_strerror(res)));
    }
    return success;
}