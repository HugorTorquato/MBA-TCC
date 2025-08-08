#include "Parser.h"

namespace
{

std::shared_ptr<IToken> peek(const std::vector<std::shared_ptr<IToken>> tokens, const int current)
{
    if (current >= tokens.size()) return nullptr;
    return tokens[current];
}

// isAtEnd() checks if we’ve run out of tokens to parse.
bool isAtEnd(const std::shared_ptr<IToken> token)
{
    if (token == nullptr) return true;
    if (token->getType() == "END_OF_FILE")
    {
        return true;
    }
    return false;
}

void advance(int& current)
{
    current++;
}

bool match(const std::initializer_list<TokenType> tokenTypesToMatch,
           const std::shared_ptr<IToken>& token, int& current)
{
    if (isAtEnd(token)) return false;

    for (auto& typeToMatch : tokenTypesToMatch)
    {
        // The validation returns true if the current token is of the given type.
        // Unlike match(), it never consumes the token, it only looks at it.
        if (token->getType() == TokenTypeNameSpace::toString(typeToMatch))
        {
            ::advance(current);
            return true;
        }
    }

    return false;
}

}  // namespace

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

std::shared_ptr<IToken> Parser::peekIndex(const int tokenIndex) const
{
    return ::peek(m_tokens, tokenIndex);
}

std::shared_ptr<IToken> Parser::peekCurrentToken() const  // Private
{
    return ::peek(m_tokens, m_current);
}

// The advance() method consumes the current token and returns it, similar to
//  how our scanner’s corresponding method crawled through characters.
std::shared_ptr<IToken> Parser::advance()  // Private
{
    if (!isAtEnd(peekCurrentToken())) ::advance(m_current);
    return previous();
}

std::shared_ptr<IToken> Parser::previous()  // Private
{
    return peekIndex(m_current - 1);
}

std::shared_ptr<Expression> Parser::equality()
{
    std::shared_ptr<Expression> expr = comparison();

    while (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken->getLexeme());
    }
    return expr;
}

std::shared_ptr<Expression> Parser::comparison()
{
    // Placeholder for the actual implementation of comparison parsing
    // This method should handle comparison operators like <, >, <=, >=
    // For now, we return an empty Expression
    std::shared_ptr<Expression> expr = comparison();

    while (match(
        {TokenType::LESS, TokenType::GREATER, TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL},
        peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken->getLexeme());
    }
    return expr;
}

std::shared_ptr<Expression> Parser::term()
{
    // Placeholder for the actual implementation of term parsing
    // This method should handle term-level expressions (e.g., addition, subtraction)
    // For now, we return an empty Expression
    std::shared_ptr<Expression> expr = comparison();

    while (match({TokenType::MINUS, TokenType::PLUS}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken->getLexeme());
    }
    return expr;
}

std::shared_ptr<Expression> Parser::factor()
{
    // Placeholder for the actual implementation of factor parsing
    // This method should handle factor-level expressions (e.g., multiplication, division)
    // For now, we return an empty Expression
    std::shared_ptr<Expression> expr = comparison();

    while (match({TokenType::SLASH, TokenType::STAR}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken->getLexeme());
    }
    return expr;
}

std::shared_ptr<Expression> Parser::unary()
{
    // Placeholder for the actual implementation of unary parsing
    // This method should handle unary operators (e.g., negation, logical NOT)
    // '    Again, we look at the current token to see how to parse. If it’s a ! or -, we must
    // have a unary expression. In that case, we grab the token, and then recursively
    // call unary() again to parse the operand.'
    std::shared_ptr<Expression> expr = comparison();

    if (match({TokenType::BANG, TokenType::MINUS}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        std::shared_ptr<Expression> right = unary();
        return std::make_shared<UnaryExpression>(operatorToken->getLexeme(), right);
    }
    return primary();
}

std::shared_ptr<Expression> Parser::primary()
{
    if (match({TokenType::FALSE}, peekCurrentToken(), m_current))
        return std::make_shared<LiteralExpression>("false");
    if (match({TokenType::TRUE}, peekCurrentToken(), m_current))
        return std::make_shared<LiteralExpression>("true");
    if (match({TokenType::NULLPTR}, peekCurrentToken(), m_current))
        return std::make_shared<LiteralExpression>("null");
    if (match({TokenType::NUMBER, TokenType::STRING}, peekCurrentToken(), m_current))
        return std::make_shared<LiteralExpression>(previous()->getLexeme());

    return nullptr;  // If no match, return nullptr
    // if(match({TokenType::LEFT_PAREN}, peekCurrentToken(), m_current))
    // {
    //     std::shared_ptr<Expression> expr = expression();
    //     consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
    //     return new GroupingExpression(expr);
    // }
}

std::shared_ptr<Expression> Parser::expression()
{
    return equality();
}