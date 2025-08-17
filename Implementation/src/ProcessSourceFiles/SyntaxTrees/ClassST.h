#pragma once

#include "CommonParserType.h"

class ClassST : public CommonParserType
{
   public:
    ClassST() = delete;

    ClassST(const std::string& className);        // Constructor receiving string
    ClassST(std::shared_ptr<IToken> classToken);  // Constructor receiving IDENTIFIER token

    std::string accept(class IPrettyPrintVisitor* visitor) override
    {
        // return visitor->ClassST(this);
        return "TODO ClassST";
    }
    std::string getType() const override
    {
        return "CLASS_DECLARATION";
    }

    std::string getClassName() const;

   private:
    std::string m_className;
};