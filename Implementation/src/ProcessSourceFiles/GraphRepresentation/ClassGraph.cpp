#include "ClassGraph.h"

#include "../../Logger/Log.h"

namespace
{
bool buildGraphValidations(const std::shared_ptr<ClassST>& cls)
{
    if (!cls)
    {
        Logger::getInstance().log(
            "[ClassGraph::buildGraph] Warning: Null class pointer encountered, skipping.");
        return false;
    }
    if (cls->getClassName().empty())
    {
        Logger::getInstance().log(
            "[ClassGraph::buildGraph] Warning: Class with empty name encountered, skipping.");
        return false;
    }
    return true;
}
}  // namespace

std::unordered_set<std::shared_ptr<ClassST>> ClassGraph::getAllClasses() const
{
    return m_nodes;
}

void ClassGraph::clear()
{
    m_parents.clear();
    m_children.clear();
    m_nodes.clear();
    m_edgeCount = 0;
}

void ClassGraph::buildGraph(const std::vector<std::shared_ptr<ClassST>>& classes)
{
    Logger::getInstance().log("[ClassGraph::buildGraph]");
    for (auto& cls : classes)
    {
        if (buildGraphValidations(cls) == false) continue;

        auto className = cls->getClassName();
        Logger::getInstance().log("[ClassGraph::buildGraph] Adding class: " + className);

        m_nodes.emplace(cls);
        auto inherencies = cls->getInherencyArray();

        // TODO: Need to ensure that there is no duplicated edges
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