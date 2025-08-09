#include "Parser.h"

#include <stdexcept>

#include "../../Logger/Log.h"

namespace
{

std::shared_ptr<IToken> peek(const std::vector<std::shared_ptr<IToken>>& tokens, const int current)
{
    Logger::getInstance().log(" [Parser][peek] tokens.size()=" + std::to_string(tokens.size()) +
                              ", current=" + std::to_string(current));
    if (current >= tokens.size()) return nullptr;
    return tokens[current];
}

// isAtEnd() checks if we’ve run out of tokens to parse.
bool isAtEnd(const std::shared_ptr<IToken> token)
{
    Logger::getInstance().log(" [Parser][isAtEnd] token=" +
                              (token ? token->toString() : "nullptr"));
    if (token == nullptr) return true;
    if (token->getType() == "END_OF_FILE")
    {
        return true;
    }
    return false;
}

void advance(int& current)
{
    Logger::getInstance().log(" [Parser][advance] current(before)=" + std::to_string(current));
    current++;
    Logger::getInstance().log(" [Parser][advance] current(after)=" + std::to_string(current));
}

bool match(const std::initializer_list<TokenType> tokenTypesToMatch,
           const std::shared_ptr<IToken>& token, int& current)
{
    std::string typesStr;
    for (auto& t : tokenTypesToMatch) typesStr += TokenTypeNameSpace::toString(t) + " ";
    Logger::getInstance().log(" [Parser][match] tokenTypesToMatch=" + typesStr +
                              ", token=" + (token ? token->toString() : "nullptr") +
                              ", current=" + std::to_string(current));
    if (isAtEnd(token)) return false;

    for (auto& typeToMatch : tokenTypesToMatch)
    {
        if (token->getTypeEnum() == typeToMatch)
        {
            ::advance(current);
            Logger::getInstance().log(" [Parser][match] matched type=" +
                                      TokenTypeNameSpace::toString(typeToMatch));
            return true;
        }
    }

    return false;
}

}  // namespace

Parser::Parser(std::vector<std::shared_ptr<IToken>> tokens) : m_tokens(std::move(tokens))
{
    Logger::getInstance().log(" [Parser][Parser] Constructed with m_tokens.size()=" +
                              std::to_string(m_tokens.size()));
}

std::vector<std::string> Parser::ListIncomingTokens() const
{
    Logger::getInstance().log(" [Parser][ListIncomingTokens] m_tokens.size()=" +
                              std::to_string(m_tokens.size()));
    std::vector<std::string> tokenList;
    for (const auto& token : m_tokens)
    {
        tokenList.push_back(token->toString());
    }
    return tokenList;
}

std::shared_ptr<IToken> Parser::peekIndex(const int tokenIndex) const
{
    Logger::getInstance().log(" [Parser][peekIndex] tokenIndex=" + std::to_string(tokenIndex));
    return ::peek(m_tokens, tokenIndex);
}

std::shared_ptr<IToken> Parser::peekCurrentToken() const  // Private
{
    Logger::getInstance().log(" [Parser][peekCurrentToken] m_current=" + std::to_string(m_current));
    return ::peek(m_tokens, m_current);
}

std::shared_ptr<IToken> Parser::advance()  // Private
{
    Logger::getInstance().log(" [Parser][advance] m_current(before)=" + std::to_string(m_current));
    if (!isAtEnd(peekCurrentToken())) ::advance(m_current);
    Logger::getInstance().log(" [Parser][advance] m_current(after)=" + std::to_string(m_current));
    return previous();
}

std::shared_ptr<IToken> Parser::previous()  // Private
{
    if (m_current == 0)
    {
        Logger::getInstance().log(" [Parser][previous] No previous token, returning nullptr.");
        return nullptr;
    }
    Logger::getInstance().log(" [Parser][previous] m_current=" + std::to_string(m_current));
    return peekIndex(m_current - 1);
}

std::shared_ptr<Expression> Parser::equality()
{
    Logger::getInstance().log(" [Parser][equality] m_current=" + std::to_string(m_current));
    std::shared_ptr<Expression> expr = comparison();

    while (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        Logger::getInstance().log(" [Parser][equality] operatorToken=" +
                                  (operatorToken ? operatorToken->toString() : "nullptr"));
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken);
    }
    return expr;
}

std::shared_ptr<Expression> Parser::comparison()
{
    Logger::getInstance().log(" [Parser][comparison] m_current=" + std::to_string(m_current));
    std::shared_ptr<Expression> expr = term();

    while (match(
        {TokenType::LESS, TokenType::GREATER, TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL},
        peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        Logger::getInstance().log(" [Parser][comparison] operatorToken=" +
                                  (operatorToken ? operatorToken->toString() : "nullptr"));
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken);
    }
    return expr;
}

std::shared_ptr<Expression> Parser::term()
{
    Logger::getInstance().log(" [Parser][term] m_current=" + std::to_string(m_current));
    std::shared_ptr<Expression> expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        Logger::getInstance().log(" [Parser][term] operatorToken=" +
                                  (operatorToken ? operatorToken->toString() : "nullptr"));
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken);
    }
    return expr;
}

std::shared_ptr<Expression> Parser::factor()
{
    Logger::getInstance().log(" [Parser][factor] m_current=" + std::to_string(m_current));
    std::shared_ptr<Expression> expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        Logger::getInstance().log(" [Parser][factor] operatorToken=" +
                                  (operatorToken ? operatorToken->toString() : "nullptr"));
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken);
    }
    return expr;
}

std::shared_ptr<Expression> Parser::unary()
{
    Logger::getInstance().log(" [Parser][unary] m_current=" + std::to_string(m_current));
    if (match({TokenType::BANG, TokenType::MINUS}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        Logger::getInstance().log(" [Parser][unary] operatorToken=" +
                                  (operatorToken ? operatorToken->toString() : "nullptr"));
        std::shared_ptr<Expression> right = unary();
        return std::make_shared<UnaryExpression>(operatorToken, right);
    }
    return primary();
}

std::shared_ptr<IToken> Parser::consume(TokenType type, const std::string& message)
{
    Logger::getInstance().log(" [Parser][consume] type=" + TokenTypeNameSpace::toString(type) +
                              ", m_current=" + std::to_string(m_current));
    auto currentToken = peekCurrentToken();
    if (currentToken && currentToken->getType() == TokenTypeNameSpace::toString(type))
    {
        return advance();
    }

    throw std::runtime_error("Parse Error at " + currentToken->getLineFile() + ": " + message);
}

std::shared_ptr<Expression> Parser::primary()
{
    Logger::getInstance().log(" [Parser][primary] m_current=" + std::to_string(m_current));
    auto currentToken = peekCurrentToken();
    Logger::getInstance().log(" [Parser][primary] currentToken=" +
                              (currentToken ? currentToken->toString() : "nullptr"));
    if (match({TokenType::FALSE}, currentToken, m_current))
        return std::make_shared<LiteralExpression>(currentToken);
    if (match({TokenType::TRUE}, currentToken, m_current))
        return std::make_shared<LiteralExpression>(currentToken);
    if (match({TokenType::NULLPTR}, currentToken, m_current))
        return std::make_shared<LiteralExpression>(currentToken);
    if (match({TokenType::NUMBER, TokenType::STRING}, currentToken, m_current))
        return std::make_shared<LiteralExpression>(currentToken);

    if (match({TokenType::LEFT_PAREN}, peekCurrentToken(), m_current))
    {
        std::shared_ptr<Expression> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<GroupingExpression>(expr);
    }

    error(currentToken, "Expect expression.");
    return nullptr;
}

std::shared_ptr<Expression> Parser::expression()
{
    Logger::getInstance().log(" [Parser][expression] m_current=" + std::to_string(m_current));
    return equality();
}

void Parser::error(std::shared_ptr<IToken> token, const std::string& message)
{
    Logger::getInstance().log(" [Parser][error] token=" + (token ? token->toString() : "nullptr") +
                              ", message=" + message);
    if (token->getType() == "END_OF_FILE")
    {
        throw std::runtime_error("Parse Error at end: " + message);
    }
    else
    {
        throw std::runtime_error("Parse Error at " + token->toString() + ": " + message);
    }
}

std::shared_ptr<Expression> Parser::parse()
{
    Logger::getInstance().log(" [Parser][parse] m_current=" + std::to_string(m_current));
    try
    {
        return expression();
    }
    catch (const std::runtime_error& e)
    {
        Logger::getInstance().log(" [Parser][parse] Exception: " + std::string(e.what()));
        return nullptr;
    }
}