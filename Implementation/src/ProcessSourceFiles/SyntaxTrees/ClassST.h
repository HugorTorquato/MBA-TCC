#pragma once

#include <memory>

#include "CommonParserType.h"

class ClassST : public CommonParserType
{
    using baseClassPair = std::pair<std::shared_ptr<IToken>, std::shared_ptr<IToken>>;

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
    std::shared_ptr<IToken> getClassToken() const;
    std::vector<ClassST::baseClassPair> getInherencyArray() const;

    void addInherencyToClassObject(std::shared_ptr<IToken> accessType,
                                   std::shared_ptr<IToken> className);

   private:
    std::string m_className;
    std::shared_ptr<IToken> m_classToken;
    std::vector<baseClassPair>
        m_inherencyArray;  // Store Array of IDENTIFIER tokens for base classes using pair to store
                           // access type and class IDENTIFIER token
};