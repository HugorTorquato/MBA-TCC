#include "ClassGraph.h"

#include <string>
#include <vector>

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

std::unordered_set<std::string> ClassGraph::getAllClasses() const
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

void ClassGraph::ensureNode(const std::string& clsName)
{
    if (clsName.empty()) return;

    if (m_nodes.insert(clsName).second)
    {
        // First Time we see this node we ensure that entries exists creating a parent and a
        // children
        Logger::getInstance().log("[ClassGraph::ensureNode] Added new node: " + clsName);
        (void)m_parents.emplace(clsName, std::vector<std::string>{});
        (void)m_children.emplace(clsName, std::vector<std::string>{});
    }
}

void ClassGraph::buildGraph(const std::vector<std::shared_ptr<ClassST>>& classes)
{
    Logger::getInstance().log("[ClassGraph::buildGraph]");
    for (auto& cls : classes)
    {
        if (buildGraphValidations(cls) == false) continue;

        auto className = cls->getClassName();
        Logger::getInstance().log("[ClassGraph::buildGraph] Adding class: " + className);

        ensureNode(className);
        // m_nodes.emplace(cls);
        auto inherencies = cls->getInherencyArray();

        // TODO: Need to ensure that there is no duplicated edges
        for (const auto& [accessTypeToken, baseClassToken] : inherencies)
        {
            Logger::getInstance().log("[ClassGraph::buildGraph] Class: " + className +
                                      " inherits from: " + baseClassToken->getLexeme() +
                                      " with access type: " + accessTypeToken->getLexeme());

            // m_parents[cls->getClassToken()] = {accessTypeToken, baseClassToken};
            // m_children[baseClassToken].push_back({accessTypeToken, cls->getClassToken()});
            m_edgeCount++;
        }
    }
}