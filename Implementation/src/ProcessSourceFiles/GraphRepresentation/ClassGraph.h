#pragma once

#include <string>
#include <unordered_set>

#include "IClassGraph.h"

class ClassGraph : public IClassGraph
{
   public:
    ClassGraph() = default;
    ~ClassGraph() override = default;

    void buildGraph(const std::vector<std::shared_ptr<ClassST>>& classes) override;
    std::unordered_set<std::string> getAllClasses() const;
    void addClassWithBases(const std::string& className,
                           const std::vector<std::string>& baseNames) override;
    void clear() override;
    size_t nodeCount() const override;
    size_t edgeCount() const override;
    bool hasNode(const std::string& name) const override;
    std::vector<std::string> nodes() const override;
    std::vector<std::string> basesOf(const std::string& name) const override;    // parents
    std::vector<std::string> derivedOf(const std::string& name) const override;  // children
    std::vector<std::string> allAncestors(const std::string& name) const override;

    std::string toDot(const std::string& graphName, bool exportToFile = false) const override;
    std::string toJsonAsString() const override;
    json toJson() const override;

   private:
    // First Time we see this node we ensure that entries exists creating a parent and a children.
    // Inserts empty vectors for the node in both maps
    void ensureNode(const std::string& clsName);
    // Check if base is already in m_parents before pushing. Mirrors the relation in m_children.
    // Increment the m_edgeCount only when a new relation is added
    void addEdge(const std::string& derived, const std::string& base);

   private:
    // derived -> bases (parents) - Allows to traverse upwards ( who do i inherit from? )
    std::unordered_map<std::string, std::vector<std::string>> m_parents;
    // base -> derived (children) - Allows to traverse downwards ( who inherits from me? )
    std::unordered_map<std::string, std::vector<std::string>> m_children;
    // all known nodes (includes bases that appear only as parents)
    std::unordered_set<std::string> m_nodes;
    size_t m_edgeCount = 0;
};
