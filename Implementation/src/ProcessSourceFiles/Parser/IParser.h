#pragma once

#include <memory>
#include <vector>

#include "../Scanner/IToken.h"
#include "../Scanner/TokenType.h"
#include "../SyntaxTrees/ClassDeclaration.h"
#include "../SyntaxTrees/Expressions.h"

class IParser
{
   public:
    virtual ~IParser() = default;

    virtual std::vector<std::string> ListIncomingTokens() const = 0;
};