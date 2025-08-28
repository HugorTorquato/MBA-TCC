#pragma once

#include <memory>

#include "../ContainersInterface/IContainersInterface.h"

class ClassST;  // forward declare so we can accept it in buildFrom

class IClassGraph
{
   public:
    virtual ~IClassGraph() = default;

    virtual void buildGraph(const std::vector<std::shared_ptr<ClassST>>& classes) = 0;
    virtual void clear() = 0;
};