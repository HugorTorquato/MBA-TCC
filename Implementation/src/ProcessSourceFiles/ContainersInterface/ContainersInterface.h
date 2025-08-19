#pragma once

#include <memory>
#include <vector>

#include "../SyntaxTrees/ClassST.h"

class ContainersInterface
{
   private:
    // Private constructor to prevent direct instantiation
    ContainersInterface();

    // Deleted copy constructor and assignment operator
    ContainersInterface(const ContainersInterface&) = delete;
    ContainersInterface& operator=(const ContainersInterface&) = delete;

   public:
    virtual ~ContainersInterface() = default;

    static ContainersInterface& getInstance();

    void addClass(std::shared_ptr<ClassST> classST);
    std::vector<std::shared_ptr<ClassST>> getClasses() const;
    std::shared_ptr<ClassST> getClassByName(const std::string& className) const;  // Problematic

    void clearClassesContainer();

   private:
    std::vector<std::shared_ptr<ClassST>> m_classesContainer;
};