#pragma once

#include <memory>

#include "../ContainersInterface/IContainersInterface.h"

class ClassST;  // forward declare so we can accept it in buildFrom

class IClassGraph
{
   public:
    virtual ~IClassGraph() = default;

    // The focus here is to extract the lexemes and add it into the graph
    virtual void buildGraph(const std::vector<std::shared_ptr<ClassST>>& classes) = 0;

    // APIs designed for validations
   public:
    // Simple way to create unit tests, just pass the name of the class and the related base classes
    virtual void addClassWithBases(const std::string& className,
                                   const std::vector<std::string>& baseNames) = 0;
    // Clear all containers from class graph
    virtual void clear() = 0;
    // Return the number of nodes evaluated
    virtual size_t nodeCount() const = 0;
    // Return the number of edges evaluated
    virtual size_t edgeCount() const = 0;

    // Queries (parents = bases; children = derived)
    // Returns true if node name ( as string ) already exists in the graph
    virtual bool hasNode(const std::string& name) const = 0;
    // Returns a sorted vecotor contianins all unique nodes evaluated
    virtual std::vector<std::string> nodes() const = 0;
    // If class exists, return the parent/children vector associated with the current class name
    // (current node)
    virtual std::vector<std::string> basesOf(const std::string& name) const = 0;    // parents
    virtual std::vector<std::string> derivedOf(const std::string& name) const = 0;  // children
    // Performa DFS search to map app the ancestors from a given class name. TODO: Implement BFS
    virtual std::vector<std::string> allAncestors(const std::string& name) const = 0;

    // Exporting
    virtual std::string toDot(const std::string& graphName) const = 0;
    //TODO: Convert this to use the JSON structure for the APIs
    virtual std::string toJson() const = 0;
};