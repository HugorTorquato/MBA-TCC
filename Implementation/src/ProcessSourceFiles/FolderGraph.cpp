#include "FolderGraph.h"

#include <memory>

ItemInFolder::ItemInFolder(const std::string& name) : name(name) {}

FolderGraph::FolderGraph(const std::string& rootName)
    : m_root(std::make_shared<ItemInFolder>(rootName))
{
}

std::shared_ptr<ItemInFolder> FolderGraph::getRoot() const
{
    return m_root;
}

void FolderGraph::addEdge(std::shared_ptr<ItemInFolder> parent, const std::string& childName)
{
    auto child = std::make_shared<ItemInFolder>(childName);
    parent->children.push_back(child);
}