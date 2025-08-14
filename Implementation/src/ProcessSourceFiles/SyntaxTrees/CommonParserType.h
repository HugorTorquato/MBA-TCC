#pragma once

#include <string>

class CommonParserType{

public:
    virtual ~CommonParserType() = default;

    virtual std::string accept(class IPrettyPrintVisitor* visitor) = 0;
    virtual std::string getType() const = 0;
};