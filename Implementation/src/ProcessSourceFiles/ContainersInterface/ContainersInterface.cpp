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
    Logger::getInstance().log("[ContainersInterface::getInstance]");
    static ContainersInterface instance;
    return instance;
}

void ContainersInterface::addClass(std::shared_ptr<ClassST> classST)
{
    if (classST)
    {
        // TODO: Check if class already exists... what to do? Ignore? Throw?
        Logger::getInstance().log("[ContainersInterface::addClass] class IDENTIFIER " +
                                  classST->getClassName());
        m_classesContainer.push_back(classST);
    }
    else
    {
        Logger::getInstance().log(
            "[ContainersInterface::addClass] Problems addding class IDENTIFIER ");
    }
}

std::vector<std::shared_ptr<ClassST>> ContainersInterface::getClasses() const
{
    Logger::getInstance().log("[ContainersInterface::getClasses]");
    return m_classesContainer;
}

std::shared_ptr<ClassST> ContainersInterface::getClassByName(const std::string& className) const
{
    Logger::getInstance().log("[ContainersInterface::getClassByName] className " + className);
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
    Logger::getInstance().log("[ContainersInterface::clearClassesContainer]");
    m_classesContainer.clear();
}