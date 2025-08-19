#include "ContainersInterface.h"

ContainersInterface::ContainersInterface() {}

ContainersInterface& ContainersInterface::getInstance()
{
    // Creates a static local variable inside the getInstance() method.
    // This ensures that the instance is created only once and persists for the lifetime of the
    // program. The first time getInstance() is called, instance is constructed. On every subsequent
    // call, the same instance object is returned. This is a thread-safe way to implement a
    // singleton in C++11 and later. Note: The static variable is initialized the first time this
    // function is called. It is destroyed when the program exits.

    static ContainersInterface instance;
    return instance;
}

void ContainersInterface::addClass(std::shared_ptr<ClassST> classST)
{
    m_classesContainer.push_back(classST);
}

std::vector<std::shared_ptr<ClassST>> ContainersInterface::getClasses() const
{
    return m_classesContainer;
}

std::shared_ptr<ClassST> ContainersInterface::getClassByName(const std::string& className) const
{
    for (const auto& classST : m_classesContainer)
    {
        if (classST->getClassName() == className)
        {
            return classST;
        }
    }
    return nullptr;  // Return nullptr if the class with the given name is not found
}

void ContainersInterface::clearClassesContainer()
{
    m_classesContainer.clear();
}