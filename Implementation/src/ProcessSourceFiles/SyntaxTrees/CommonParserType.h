#pragma once

#include <memory>
#include <string>

#include "../Scanner/IToken.h"

class CommonParserType
{
   public:
    virtual ~CommonParserType() = default;

    virtual std::string accept(class IPrettyPrintVisitor* visitor) = 0;
    virtual std::string getType() const = 0;
};