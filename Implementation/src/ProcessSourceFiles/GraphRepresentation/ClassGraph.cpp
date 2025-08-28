#include "ClassGraph.h"

#include <algorithm>
#include <stack>
#include <string>
#include <unordered_set>
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

std::vector<std::string> sortReturnVector(const std::vector<std::string>& v)
{
    auto vCopy = v;
    std::sort(vCopy.begin(), vCopy.end());
    return vCopy;
}
}  // namespace

std::unordered_set<std::string> ClassGraph::getAllClasses() const
{
    Logger::getInstance().log("[ClassGraph::getAllClasses] Returning all class nodes.");
    return m_nodes;
}

size_t ClassGraph::nodeCount() const
{
    return m_nodes.size();
}

size_t ClassGraph::edgeCount() const
{
    return m_edgeCount;
}

void ClassGraph::clear()
{
    Logger::getInstance().log("[ClassGraph::clear] Clearing all graph data.");
    m_parents.clear();
    m_children.clear();
    m_nodes.clear();
    m_edgeCount = 0;
    Logger::getInstance().log("[ClassGraph::clear] Graph data cleared.");
}

void ClassGraph::addClassWithBases(const std::string& className,
                                   const std::vector<std::string>& baseNames)
{
    Logger::getInstance().log("[ClassGraph::addClassWithBases] Adding class: " + className +
                              " with bases.");
    if (className.empty())
    {
        Logger::getInstance().log(
            "[ClassGraph::addClassWithBases] Empty class name or base names, skipping.");
        return;
    }

    ensureNode(className);

    for (const auto& baseName : baseNames)
    {
        Logger::getInstance().log("[ClassGraph::addClassWithBases] Adding base: " + baseName +
                                  " to class: " + className);
        addEdge(className, baseName);
    }
    Logger::getInstance().log("[ClassGraph::addClassWithBases] Finished adding bases for class: " +
                              className);
}

void ClassGraph::ensureNode(const std::string& clsName)
{
    if (clsName.empty()) return;

    if (m_nodes.insert(clsName).second)
    {
        Logger::getInstance().log("[ClassGraph::ensureNode] Added new node: " + clsName);
        (void)m_parents.emplace(clsName, std::vector<std::string>{});
        (void)m_children.emplace(clsName, std::vector<std::string>{});
    }
}

void ClassGraph::addEdge(const std::string& derived, const std::string& base)
{
    ensureNode(derived);
    ensureNode(base);

    Logger::getInstance().log("[ClassGraph::addEdge] Attempting to add edge: " + derived + " -> " +
                              base);

    // Avoid duplicates in m_parents
    auto& parentsVector = m_parents[derived];
    if (std::find(parentsVector.begin(), parentsVector.end(), base) == parentsVector.end())
    {
        parentsVector.push_back(base);
        Logger::getInstance().log("[ClassGraph::addEdge] Added parent: " + base +
                                  " to derived: " + derived);
    }
    else
    {
        Logger::getInstance().log("[ClassGraph::addEdge] Edge already exists: " + derived + " -> " +
                                  base + ", skipping.");
        return;
    }

    // Avoid duplicates in m_children
    auto& childrenVector = m_children[base];
    if (std::find(childrenVector.begin(), childrenVector.end(), derived) == childrenVector.end())
    {
        childrenVector.push_back(derived);
        Logger::getInstance().log("[ClassGraph::addEdge] Added child: " + derived +
                                  " to base: " + base);
    }

    ++m_edgeCount;
    Logger::getInstance().log("[ClassGraph::addEdge] Edge count incremented to: " +
                              std::to_string(m_edgeCount));
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
        auto inherencies = cls->getInherencyArray();

        // TODO: Need to ensure that there is no duplicated edges
        for (const auto& [accessTypeToken, baseClassToken] : inherencies)
        {
            if (baseClassToken)
            {
                auto baseClassName = baseClassToken->getLexeme();
                Logger::getInstance().log("[ClassGraph::buildGraph] Class: " + className +
                                          " inherits from: " + baseClassName +
                                          " with access type: " + accessTypeToken->getLexeme());

                addEdge(className, baseClassName);
            }
        }
    }
}
bool ClassGraph::hasNode(const std::string& name) const
{
    Logger::getInstance().log("[ClassGraph::hasNode] Checking if node exists: " + name);
    bool exists = m_nodes.find(name) != m_nodes.end();
    Logger::getInstance().log("[ClassGraph::hasNode] Node " + name +
                              (exists ? " exists." : " does not exist."));
    return exists;
}

std::vector<std::string> ClassGraph::nodes() const
{
    Logger::getInstance().log("[ClassGraph::nodes] Collecting all nodes for sorting.");
    std::vector<std::string> sortedVector{m_nodes.begin(), m_nodes.end()};
    std::sort(sortedVector.begin(), sortedVector.end());
    Logger::getInstance().log("[ClassGraph::nodes] Returning sorted list of nodes. Count: " +
                              std::to_string(sortedVector.size()));
    return sortedVector;
}

std::vector<std::string> ClassGraph::basesOf(const std::string& name) const
{
    Logger::getInstance().log("[ClassGraph::basesOf] Getting bases of class: " + name);
    auto it = m_parents.find(name);
    if (it == m_parents.end())
    {
        Logger::getInstance().log("[ClassGraph::basesOf] Class not found: " + name +
                                  ". Returning empty vector.");
        return {};
    }
    Logger::getInstance().log("[ClassGraph::basesOf] Found bases for class: " + name +
                              ". Count: " + std::to_string(it->second.size()));
    return sortReturnVector(it->second);
}

std::vector<std::string> ClassGraph::derivedOf(const std::string& name) const
{
    Logger::getInstance().log("[ClassGraph::derivedOf] Getting derived classes of: " + name);
    auto it = m_children.find(name);
    if (it == m_children.end())
    {
        Logger::getInstance().log("[ClassGraph::derivedOf] Class not found: " + name +
                                  ". Returning empty vector.");
        return {};
    }
    Logger::getInstance().log("[ClassGraph::derivedOf] Found derived classes for: " + name +
                              ". Count: " + std::to_string(it->second.size()));
    return sortReturnVector(it->second);
}

std::vector<std::string> ClassGraph::allAncestors(const std::string& name) const
{
    Logger::getInstance().log("[ClassGraph::allAncestors] Collecting all ancestors for: " + name);
    std::vector<std::string> result;
    if (!hasNode(name))
    {
        Logger::getInstance().log("[ClassGraph::allAncestors] Node not found: " + name +
                                  ". Returning empty vector.");
        return result;
    }

    std::unordered_set<std::string> visited;
    std::stack<std::string> st;

    st.push(name);
    Logger::getInstance().log("[ClassGraph::allAncestors] Starting traversal from: " + name);

    // DFS traversal to collect all ancestors
    while (!st.empty())
    {
        auto cur = st.top();
        st.pop();

        auto it = m_parents.find(cur);
        if (it == m_parents.end()) continue;

        for (const auto& base : it->second)
        {
            if (!visited.count(base))
            {
                Logger::getInstance().log("[ClassGraph::allAncestors] Found ancestor: " + base +
                                          " of " + cur);
                visited.insert(base);
                result.push_back(base);
                st.push(base);
            }
        }
    }

    Logger::getInstance().log("[ClassGraph::allAncestors] Total ancestors found for " + name +
                              ": " + std::to_string(result.size()));
    return sortReturnVector(result);
}

std::string ClassGraph::toDot(const std::string& graphName) const
{
    Logger::getInstance().log("[ClassGraph::toDot] Generating DOT representation for graph: " +
                              graphName);
    std::string out = "digraph " + graphName + " {\n";
    // nodes (optional, but helps show bases that have no parents/children)
    for (const auto& n : m_nodes)
    {
        Logger::getInstance().log("[ClassGraph::toDot] Adding node to DOT: " + n);
        out += "  \"" + n + "\";\n";
    }
    // edges derived -> base
    for (const auto& [derived, bases] : m_parents)
    {
        for (const auto& base : bases)
        {
            Logger::getInstance().log("[ClassGraph::toDot] Adding edge to DOT: " + derived +
                                      " -> " + base);
            out += "  \"" + derived + "\" -> \"" + base + "\";\n";
        }
    }
    out += "}\n";
    Logger::getInstance().log("[ClassGraph::toDot] DOT generation complete.");
    return out;
}

std::string ClassGraph::toJson() const {
    Logger::getInstance().log("[ClassGraph::toJson] Generating JSON representation of the graph.");
    std::string out = "{";
    bool firstNode = true;
    // deterministic order
    std::vector<std::string> nodesVec{m_nodes.begin(), m_nodes.end()};
    std::sort(nodesVec.begin(), nodesVec.end());
    Logger::getInstance().log("[ClassGraph::toJson] Sorted nodes for deterministic output.");

    for (const auto& n : nodesVec) {
        if (!firstNode) out += ",";
        firstNode = false;

        Logger::getInstance().log("[ClassGraph::toJson] Processing node: " + n);
        out += "\"" + n + "\":[";
        auto it = m_parents.find(n);
        if (it != m_parents.end()) {
            auto v = it->second;
            std::sort(v.begin(), v.end());
            Logger::getInstance().log("[ClassGraph::toJson] Sorted parents for node: " + n);
            for (size_t i = 0; i < v.size(); ++i) {
                if (i) out += ",";
                Logger::getInstance().log("[ClassGraph::toJson] Adding parent: " + v[i] + " to node: " + n);
                out += "\"" + v[i] + "\"";
            }
        }
        out += "]";
    }
    out += "}";
    Logger::getInstance().log("[ClassGraph::toJson] JSON generation complete.");
    return out;
}
