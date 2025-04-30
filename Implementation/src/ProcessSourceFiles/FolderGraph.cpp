#include "FolderGraph.h"

#include <cstring>
#include <memory>

#include "../Logger/Log.h"

ItemInFolder::ItemInFolder(const std::string& name, const std::string& type) : m_name(name)
{
    if (type == "dir")
        m_type = ItemEnumType::DIR;
    else if (type == "file")
        m_type = ItemEnumType::SOURCEFILE;
    else
    {
        m_type = ItemEnumType::UNKNOWN;
        Logger::getInstance().log("Warning: Unknown item type: " + type);
    }
}

void ItemInFolder::addChild(const std::shared_ptr<ItemInFolder>& child)
{
    m_children.push_back(child);
}
void ItemInFolder::addChild(const std::string& childName, const std::string& type)
{
    auto child = std::make_shared<ItemInFolder>(childName, type);
    m_children.push_back(child);
}

std::string ItemInFolder::getName() const
{
    return m_name;
}
ItemEnumType ItemInFolder::getType() const
{
    return m_type;
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

void FolderGraph::addEdge(std::shared_ptr<ItemInFolder> parent, const std::string& childName,
                          const std::string& type)
{
    auto child = std::make_shared<ItemInFolder>(childName, type);
    parent->addChild(child);
}

void FolderGraph::addEdge(std::shared_ptr<ItemInFolder> parent,
                          const std::shared_ptr<ItemInFolder>& child)
{
    parent->addChild(child);
}