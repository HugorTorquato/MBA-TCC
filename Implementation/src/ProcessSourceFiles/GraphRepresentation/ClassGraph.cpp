#include "ClassGraph.h"

#include "../../Logger/Log.h"

std::unordered_set<std::shared_ptr<ClassST>> ClassGraph::getAllClasses() const
{
    return m_nodes;
}

void ClassGraph::buildGraph(const std::vector<std::shared_ptr<ClassST>>& classes)
{
    Logger::getInstance().log("[ClassGraph::buildGraph]");
    for (auto& cls : classes)
    {
        if(!cls)
        {
            Logger::getInstance().log(
                "[ClassGraph::buildGraph] Warning: Null class pointer encountered, skipping.");
            continue;
        }
        auto className = cls->getClassName();
        if (className.empty())
        {
            Logger::getInstance().log(
                "[ClassGraph::buildGraph] Warning: Class with empty name encountered, skipping.");
            continue;
        }
        Logger::getInstance().log("[ClassGraph::buildGraph] Adding class: " + className);

        m_nodes.emplace(cls);
        auto inherencies = cls->getInherencyArray();

        //TODO: Need to ensure that there is no duplicated edges
        for (const auto& [accessTypeToken, baseClassToken] : inherencies)
        {
            Logger::getInstance().log("[ClassGraph::buildGraph] Class: " + className +
                                      " inherits from: " + baseClassToken->getLexeme() +
                                      " with access type: " + accessTypeToken->getLexeme());

            m_parents[cls->getClassToken()] = {accessTypeToken, baseClassToken};
            m_children[baseClassToken].push_back({accessTypeToken, cls->getClassToken()});
            m_edgeCount++;
        }
    }
}