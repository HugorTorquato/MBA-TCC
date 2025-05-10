#include "HttpClient.h"

#include <curl/curl.h>
#include <curl/easy.h>

#include <filesystem>
#include <stdexcept>
#include <string>

#include "../../Logger/Log.h"

namespace fs = std::filesystem;

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

size_t writeToFileCallback(void* ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* file = static_cast<FILE*>(userdata);
    return fwrite(ptr, size, nmemb, file);
}

void verifyErrorWithCurlResponse(const CURLcode& res)
{
    if (res != CURLE_OK)
    {
        Logger::getInstance().log(
            std::string("[CurlHttpClient::verifyErrorWithCurlResponse] Error with curl: %s",
                        curl_easy_strerror(res)));
        throw std::runtime_error("Error with curl: " + std::string(curl_easy_strerror(res)));
    }
}

struct curl_slist* defineHeaders()
{
    // Load GitHub token from environment
    const char* tokenEnv = std::getenv("GITHUB_TOKEN");
    std::string token = tokenEnv ? tokenEnv : "";

    // Logger::getInstance().log("[CurlHttpClient::defineHeaders] Token: " +
    //                           token);  // For debugging purposes

    struct curl_slist* headers = nullptr;
    if (!token.empty())
    {
        headers = curl_slist_append(headers, ("Authorization: token " + token).c_str());
        headers = curl_slist_append(headers, "Accept: application/vnd.github+json");
    }

    return headers;
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
    auto headers = defineHeaders();

    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback.value_or(writeToStringCallback));
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "Crow-GitHub-Agent");
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 20L);

    CURLcode res = curl_easy_perform(m_curl);
    verifyErrorWithCurlResponse(res);

    return (res == CURLE_OK);
}

// Responsible for downloading a file from a given URL and saving it to a specified output path.
bool CurlHttpClient::downloadFile(
    const std::string& url, const std::string& outputPath,
    std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback)
{
    if (!m_curl)
    {
        Logger::getInstance().log("[CurlHttpClient::downloadFile] CURL not initialized");
        throw std::runtime_error("CURL not initialized");
    }

    Logger::getInstance().log("[CurlHttpClient::downloadFile] Fetching URL: " + url);

    fs::create_directories(fs::path(outputPath).parent_path());
    FILE* file = fopen(outputPath.c_str(), "wb");
    if (!file)
    {
        Logger::getInstance().log("[CurlHttpClient::downloadFile] Failed to open file: " +
                                  outputPath);
        throw std::runtime_error("Failed to open file: " + outputPath);
    }

    auto headers = defineHeaders();

    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback.value_or(writeToFileCallback));
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 20L);

    CURLcode res = curl_easy_perform(m_curl);
    fclose(file);

    verifyErrorWithCurlResponse(res);

    Logger::getInstance().log("[CurlHttpClient::downloadFile] File downloaded successfully to: " +
                              outputPath);
    return (res == CURLE_OK);
}