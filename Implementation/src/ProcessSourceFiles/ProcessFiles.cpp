#include "ProcessFiles.h"

#include <stdexcept>

namespace
{

}  // namespace

DownloadFiles::DownloadFiles(const std::string& originalURL) : m_originalURL(originalURL)
{
    // MUST call this constructor to instantiate this object.
    if (originalURL.empty())
    {
        throw std::invalid_argument("URL cannot be empty");
    }
}

std::string DownloadFiles::getOriginalURL()
{
    return m_originalURL;
}