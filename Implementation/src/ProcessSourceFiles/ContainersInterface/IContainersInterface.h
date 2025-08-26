#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../SyntaxTrees/ClassST.h"

class IContainersInterface
{
   public:
    virtual ~IContainersInterface() = default;

    // Add a class into the container
    virtual void addClass(std::shared_ptr<ClassST> classST) = 0;

    // Retrieve all classes
    virtual std::vector<std::shared_ptr<ClassST>> getClasses() const = 0;

    // Retrieve by name (returns nullptr if not found)
    virtual std::shared_ptr<ClassST> getClassByName(const std::string& className) const = 0;

    // Clear all classes
    virtual void clearClassesContainer() = 0;
};
