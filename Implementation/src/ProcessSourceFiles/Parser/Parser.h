#pragma once

#include "IParser.h"

class Parser : public IParser
{
   public:
    Parser(std::vector<std::shared_ptr<IToken>> tokens);
    virtual ~Parser() = default;

    std::vector<std::string> ListIncomingTokens() const override;

   private:
    int current = 0;
    std::vector<std::shared_ptr<IToken>> m_tokens;
};