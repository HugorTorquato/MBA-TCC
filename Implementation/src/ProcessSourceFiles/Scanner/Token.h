#pragma once

#include <string>

#include "../util/LineFile.h"
#include "IToken.h"
#include "TokenType.h"

class Token : public IToken
{
   public:
    Token() = default;
    Token(TokenType type, const std::string& lexeme, const LineFile& lineFile);

    std::string getType() const;
    std::string getLexeme() const;
    std::string getLineFile() const;

    std::string toString() const;

   private:
    TokenType m_type;
    std::string m_lexeme;
    LineFile m_lineFile;
};