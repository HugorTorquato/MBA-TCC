#pragma once

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

    std::unordered_set<std::shared_ptr<ClassST>> getAllClasses() const;
    void clear() override;

   private:
    // TODO: This will not be string to string. ClassST or token?

    // derived -> bases (parents)
    std::unordered_map<std::shared_ptr<IToken>, baseClassPair> m_parents;
    // base -> derived (children)
    std::unordered_map<std::shared_ptr<IToken>, std::vector<baseClassPair>> m_children;
    // all known nodes (includes bases that appear only as parents)
    std::unordered_set<std::shared_ptr<ClassST>> m_nodes;
    size_t m_edgeCount = 0;
};
