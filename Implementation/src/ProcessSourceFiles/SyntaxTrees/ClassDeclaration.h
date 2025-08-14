#pragma once

#include "CommonParserType.h"

class ClassDeclaration : public CommonParserType
{
public:

    ClassDeclaration() = delete;

    std::string accept(class IPrettyPrintVisitor* visitor) override
    {
        // return visitor->visitClassDeclaration(this);
        return "TODO ClassDeclarationVisitor";
    }
    std::string getType() const override
    {
        return "CLASS_DECLARATION";
    }
};