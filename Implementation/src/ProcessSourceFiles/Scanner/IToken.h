#pragma once

#include <string>
#include <vector>

#include "../util/LineFile.h"
#include "TokenType.h"

class IToken
{
   public:
    virtual ~IToken() = default;

    virtual std::string getType() const = 0;
    virtual TokenType getTypeEnum() const = 0;
    virtual std::string getLexeme() const = 0;
    virtual std::string getLineFile() const = 0;
    virtual LineFile getLineFileObj() const = 0;

    virtual std::string toString() const = 0;
};