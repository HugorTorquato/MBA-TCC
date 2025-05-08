#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <variant>
#include <vector>

enum ItemEnumType
{
    SOURCEFILE,
    DIR,
    UNKNOWN
};

enum class PropertySelector
{
    Name,
    Path,
    Size,
    Url,
    HtmlUrl,
    GitUrl,
    DownloadUrl,
    Type
};

class ItemInFolder
{
   public:
    ItemInFolder() = delete;  // Can only initialize a node with a name
    // ItemInFolder(const std::string& name, const std::string& type);
    ItemInFolder(const std::string& name, const std::string& path, const unsigned int size,
                 const std::string& url, const std::string& html_url, const std::string& git_url,
                 const std::string& download_url, const std::string& type);

    void addChild(const std::shared_ptr<ItemInFolder>& child);
    void addChild(const std::string& childName, const std::string& type);

    std::string getName() const;
    std::filesystem::path getPath() const;
    unsigned int getSize() const;
    std::string getUrl() const;
    std::string getHtmlUrl() const;
    std::string getGitUrl() const;
    std::string getDownloadUrl() const;
    ItemEnumType getType() const;

    void setName(const std::string& name);
    void setPath(const std::string& path);
    void setSize(const unsigned int size);
    void setUrl(const std::string& url);
    void setHtmlUrl(const std::string& gitUrl);
    void setGitUrl(const std::string& name);
    void setDownloadUrl(const std::string& downloadUrl);
    void setType(const std::string& type);

    std::vector<std::shared_ptr<ItemInFolder>>& getChildren();

    // TODO: Create a especialization for this string URL links.... so i can verify things there
   private:
    std::string m_name;
    std::filesystem::path m_path;
    unsigned int m_size;
    std::string m_url;
    std::string m_html_url;
    std::string m_git_url;
    std::string m_download_url;
    ItemEnumType m_type;

    std::vector<std::shared_ptr<ItemInFolder>> m_children;
};

class FolderGraph
{
   public:
    FolderGraph() = delete;  // Can only instantiate this with a root
    // FolderGraph(const std::string& rootName);
    FolderGraph(const std::shared_ptr<ItemInFolder>& root);

    std::shared_ptr<ItemInFolder> getRoot() const;
    void addEdge(std::shared_ptr<ItemInFolder> parent, const std::string& childName,
                 const std::string& type);
    void addEdge(std::shared_ptr<ItemInFolder> parent, const std::shared_ptr<ItemInFolder>& child);

    using PropertyValue =
        std::variant<std::string, std::filesystem::path, unsigned int, ItemEnumType>;
    using NamedProperty = std::pair<std::string, PropertyValue>;

    PropertyValue extractProperty(const std::shared_ptr<ItemInFolder>& node,
                                  PropertySelector selector);
    std::vector<FolderGraph::NamedProperty> dfsToJson(const std::shared_ptr<ItemInFolder>& node,
                                                      PropertySelector selector);

   private:
    std::shared_ptr<ItemInFolder> m_root;
    // std::vector<std::shared_ptr<ItemInFolder>> allItems;
    // std::vector<std::string> allItemsNames;

    // I need a easy way to traverse it and get list of informations...
    // traverse function speciifing the type of information to get
    // Need to add more information items from json response from each node
    // Get The path from each node in the graph
    // root ->Folder1 -> File 1
};