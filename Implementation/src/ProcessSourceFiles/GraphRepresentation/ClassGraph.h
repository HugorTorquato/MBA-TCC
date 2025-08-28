#pragma once

#include <string>
#include <unordered_set>

#include "IClassGraph.h"

class ClassGraph : public IClassGraph
{
    // TODO: How to reuse this definition from ClassST.h
    using baseClassPair = std::pair<std::shared_ptr<IToken>, std::shared_ptr<IToken>>;

   public:
    ClassGraph() = default;
    ~ClassGraph() override = default;

    void buildGraph(const std::vector<std::shared_ptr<ClassST>>& classes) override;

    std::unordered_set<std::string> getAllClasses() const;
    void clear() override;

    void ensureNode(const std::string& clsName);

   private:
    // TODO: This will not be string to string. ClassST or token?

    // derived -> bases (parents)
    std::unordered_map<std::string, std::vector<std::string>> m_parents;
    // base -> derived (children)
    std::unordered_map<std::string, std::vector<std::string>> m_children;
    // all known nodes (includes bases that appear only as parents)
    std::unordered_set<std::string> m_nodes;
    size_t m_edgeCount = 0;
};
