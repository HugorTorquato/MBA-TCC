#include "FolderGraph.h"

#include <cstring>
#include <memory>

#include "../Logger/Log.h"

namespace
{
ItemEnumType getItemTypeFromString(const std::string& type)
{
    if (type == "dir") return ItemEnumType::DIR;
    if (type == "file") return ItemEnumType::SOURCEFILE;
    Logger::getInstance().log("[FolderGraph][getItemTypeFromString] Warning: Unknown item type: " +
                              type);
    return ItemEnumType::UNKNOWN;
}
}  // namespace

ItemInFolder::ItemInFolder(const std::string& name, const std::string& path,
                           const unsigned int size, const std::string& url,
                           const std::string& html_url, const std::string& git_url,
                           const std::string& download_url, const std::string& type)
    : m_name(name),
      m_path(std::filesystem::path(path)),
      m_size(size),
      m_url(url),
      m_html_url(html_url),
      m_git_url(git_url),
      m_download_url(download_url),
      m_type(getItemTypeFromString(type))
{
    // Decided not to process JSON files in here...
    // need to receive the values already parsed or as str
}

void ItemInFolder::addChild(const std::shared_ptr<ItemInFolder>& child)
{
    m_children.push_back(child);
}

// void ItemInFolder::addChild(const std::string& childName, const std::string& type)
// {
//     auto child = std::make_shared<ItemInFolder>(childName, type);
//     m_children.push_back(child);
// }

std::string ItemInFolder::getName() const
{
    return m_name;
}

std::filesystem::path ItemInFolder::getPath() const
{
    return m_path;
}

unsigned int ItemInFolder::getSize() const
{
    return m_size;
}

std::string ItemInFolder::getUrl() const
{
    return m_url;
}

std::string ItemInFolder::getHtmlUrl() const
{
    return m_html_url;
}

std::string ItemInFolder::getGitUrl() const
{
    return m_git_url;
}

std::string ItemInFolder::getDownloadUrl() const
{
    return m_download_url;
}

ItemEnumType ItemInFolder::getType() const
{
    return m_type;
}

void ItemInFolder::setName(const std::string& name)
{
    m_name = name;
}

void ItemInFolder::setPath(const std::string& path)
{
    m_path = std::filesystem::path(path);
}

void ItemInFolder::setSize(const unsigned int size)
{
    m_size = size;
}

void ItemInFolder::setUrl(const std::string& url)
{
    m_url = url;
}

void ItemInFolder::setHtmlUrl(const std::string& gitUrl)
{
    m_html_url = gitUrl;
}

void ItemInFolder::setGitUrl(const std::string& name)
{
    m_git_url = name;
}

void ItemInFolder::setDownloadUrl(const std::string& downloadUrl)
{
    m_download_url = downloadUrl;
}

void ItemInFolder::setType(const std::string& type)
{
    if (type == "dir")
        m_type = ItemEnumType::DIR;
    else if (type == "file")
        m_type = ItemEnumType::SOURCEFILE;
    else
    {
        m_type = ItemEnumType::UNKNOWN;
        Logger::getInstance().log("[ItemInFolder::setType] Warning: Unknown item type: " + type);
    }
}

std::vector<std::shared_ptr<ItemInFolder>>& ItemInFolder::getChildren()
{
    return m_children;
}

// FolderGraph::FolderGraph(const std::string& rootName)
//     : m_root(std::make_shared<ItemInFolder>(rootName))
// {
// }

FolderGraph::FolderGraph(const std::shared_ptr<ItemInFolder>& root) : m_root(root)
{
    // Root can only be created with ItemInFolder obj.
}

std::shared_ptr<ItemInFolder> FolderGraph::getRoot() const
{
    return m_root;
}

// void FolderGraph::addEdge(std::shared_ptr<ItemInFolder> parent, const std::string& childName,
//                           const std::string& type)
// {
//     auto child = std::make_shared<ItemInFolder>(childName, type);
//     parent->addChild(child);
// }

void FolderGraph::addEdge(std::shared_ptr<ItemInFolder> parent,
                          const std::shared_ptr<ItemInFolder>& child)
{
    parent->addChild(child);
}

FolderGraph::PropertyValue FolderGraph::extractProperty(const std::shared_ptr<ItemInFolder>& node,
                                                        PropertySelector selector)
{
    switch (selector)
    {
        case PropertySelector::Name:
            return node->getName();
        case PropertySelector::Path:
            return node->getPath();
        case PropertySelector::Size:
            return node->getSize();
        case PropertySelector::Url:
            return node->getUrl();
        case PropertySelector::HtmlUrl:
            return node->getHtmlUrl();
        case PropertySelector::GitUrl:
            return node->getGitUrl();
        case PropertySelector::DownloadUrl:
            return node->getDownloadUrl();
        case PropertySelector::Type:
            return node->getType();
    }
    throw std::invalid_argument("Unknown selector");
}

std::vector<FolderGraph::NamedProperty> FolderGraph::dfsToJson(
    const std::shared_ptr<ItemInFolder>& node, PropertySelector selector)
{
    Logger::getInstance().log("[FolderGraph::dfsToJson] node: " + node->getName() +
                              " selector: " + std::to_string(static_cast<int>(selector)));
    if (!node) return {};

    // vector would have folder path and the selected function
    std::vector<FolderGraph::NamedProperty> result;
    auto value = extractProperty(node, selector);

    result.emplace_back(node->getName(), value);
    for (const auto& child : node->getChildren())
    {
        Logger::getInstance().log("[FolderGraph::dfsToJson] child: " + child->getName());
        auto childResult = dfsToJson(child, selector);
        result.insert(result.end(), childResult.begin(), childResult.end());
    }
    return result;
}
