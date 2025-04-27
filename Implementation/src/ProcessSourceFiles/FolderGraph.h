#pragma once

#include <memory>
#include <string>
#include <vector>

class ItemInFolder
{
   public:
    std::string name;
    std::vector<std::shared_ptr<ItemInFolder>> children;

    ItemInFolder() = delete;  // Can only initialize a node with a name
    ItemInFolder(const std::string& name);
};

class FolderGraph
{
   public:
    FolderGraph() = delete;  // Can only instantiate this with a root
    FolderGraph(const std::string& rootName);

    std::shared_ptr<ItemInFolder> getRoot() const;
    void addEdge(std::shared_ptr<ItemInFolder> parent, const std::string& childName);

   private:
    std::shared_ptr<ItemInFolder> m_root;
    // std::vector<std::shared_ptr<ItemInFolder>> allItems;
    // std::vector<std::string> allItemsNames;
};