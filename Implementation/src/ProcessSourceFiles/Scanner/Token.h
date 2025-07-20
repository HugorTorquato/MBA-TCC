#pragma once

#include <string>

#include "../util/LineFile.h"
#include "IToken.h"
#include "TokenType.h"

class Token : public IToken
{
   public:
    Token(TokenType type, const std::string& lexeme, const LineFile& lineFile);

    std::string getType() const override;
    std::string getLexeme() const override;
    std::string getLineFile() const override;

    std::string toString() const override;

   private:
    TokenType m_type;
    std::string m_lexeme;
    LineFile m_lineFile;
};