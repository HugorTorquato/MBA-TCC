#pragma once

#include "IParser.h"

class Parser : public IParser
{
   public:
    Parser(std::vector<std::shared_ptr<IToken>> tokens);
    virtual ~Parser() = default;

    std::vector<std::string> ListIncomingTokens() const override;

    std::shared_ptr<Expression> expression();

    std::shared_ptr<IToken> peekIndex(const int tokenIndex) const;

   private:
    std::shared_ptr<IToken> peekCurrentToken()
        const;  // peek() returns the current token we have yet to consume
    std::shared_ptr<IToken> advance();
    std::shared_ptr<IToken> previous();  // previous() returns the most recently consumed token.

    std::shared_ptr<Expression>
    equality();  // Parses equality expressions, such as `a == b` or `a != b`
    std::shared_ptr<Expression>
    comparison();  // Placeholder for the actual implementation of comparison parsing
    std::shared_ptr<Expression>
    term();  // Placeholder for the actual implementation of term parsing
    std::shared_ptr<Expression>
    factor();  // Placeholder for the actual implementation of factor parsing
    std::shared_ptr<Expression>
    unary();  // Placeholder for the actual implementation of unary parsing
    std::shared_ptr<Expression>
    primary();  // Placeholder for the actual implementation of primary parsing

   private:
    int m_current = 0;
    std::vector<std::shared_ptr<IToken>> m_tokens;
};