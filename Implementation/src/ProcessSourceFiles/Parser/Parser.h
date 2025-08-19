#pragma once

#include <memory>

#include "IParser.h"

class Parser : public IParser
{
   public:
    Parser(std::vector<std::shared_ptr<IToken>> tokens);
    virtual ~Parser() = default;

    std::vector<std::string> ListIncomingTokens() const override;
    std::shared_ptr<Expression> expression();
    std::shared_ptr<CommonParserType> parse();  // define an initial method to kick it off.
    std::shared_ptr<IToken> peekIndex(const int tokenIndex) const;

   private:
    std::shared_ptr<IToken> peekCurrentToken()
        const;  // peek() returns the current token we have yet to consume
    std::shared_ptr<IToken> advance();
    std::shared_ptr<IToken> consume(TokenType type, const std::string& message);
    std::shared_ptr<IToken> previous();  // previous() returns the most recently consumed token.

    void error(std::shared_ptr<IToken> token, const std::string& message);
    bool check(
        const TokenType type) const;  // check() checks if the current token is of a specific type

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

    std::shared_ptr<ClassST> classDeclaration();  // Parses class declarations

   private:
    int m_current = 0;
    std::vector<std::shared_ptr<IToken>> m_tokens;
};