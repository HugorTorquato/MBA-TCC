#pragma once

#include <memory>
#include <string>
#include <vector>

class ItemInFolder
{
   public:
    ItemInFolder() = delete;  // Can only initialize a node with a name
    ItemInFolder(const std::string& name, const std::string& type);

    void addChild(const std::shared_ptr<ItemInFolder>& child);
    void addChild(const std::string& childName, const std::string& type);

    std::string getName() const;
    std::string getType() const;  // TODO: create an enum for this
    std::vector<std::shared_ptr<ItemInFolder>>& getChildren();

   private:
    std::string m_name;
    std::string m_type;
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

   private:
    std::shared_ptr<ItemInFolder> m_root;
    // std::vector<std::shared_ptr<ItemInFolder>> allItems;
    // std::vector<std::string> allItemsNames;
};