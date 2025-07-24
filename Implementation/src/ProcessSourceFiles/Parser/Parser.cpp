#include "Parser.h"

Parser::Parser(std::vector<std::shared_ptr<IToken>> tokens) : m_tokens(std::move(tokens)) {}

std::vector<std::string> Parser::ListIncomingTokens() const
{
    std::vector<std::string> tokenList;
    for (const auto& token : m_tokens)
    {
        tokenList.push_back(token->toString());
    }
    return tokenList;
}
