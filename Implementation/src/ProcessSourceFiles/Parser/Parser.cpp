#include "Parser.h"

#include <stdexcept>

#include "../../Logger/Log.h"

using std::runtime_error;

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

    if (isAtEnd(token))
    {
        Logger::getInstance().log(" [Parser][match] token is at end, returning false.");
        return false;
    }
    if (tokenTypesToMatch.size() == 0)
    {
        Logger::getInstance().log(" [Parser][match] No token types to match, returning false.");
        return false;
    }

    Logger::getInstance().log(" [Parser][match] tokenTypesToMatch.size()=" +
                              std::to_string(tokenTypesToMatch.size()));

    for (auto& typeToMatch : tokenTypesToMatch)
    {
        typesStr += TokenTypeNameSpace::toString(typeToMatch) + " ";
        Logger::getInstance().log(
            " [Parser][match] Checking token type: " +
            std::to_string(token->getTypeEnum() == typeToMatch) + " typesStr : " + typesStr +
            " typeToMatch: " + std::to_string((int)typeToMatch) +
            ", token->getTypeEnum(): " + std::to_string((int)token->getTypeEnum()) +
            ", token=" + token->toString() + ", current=" + std::to_string(current));

        if (token->getTypeEnum() == typeToMatch)
        {
            ::advance(current);
            Logger::getInstance().log(" [Parser][match] matched type=" +
                                      TokenTypeNameSpace::toString(typeToMatch));
            return true;
        }
        else
        {
            Logger::getInstance().log(" [Parser][match] type mismatch: expected=" +
                                      TokenTypeNameSpace::toString(typeToMatch) + ", found=" +
                                      TokenTypeNameSpace::toString(token->getTypeEnum()));
        }
    }

    Logger::getInstance().log(" [Parser][match] tokenTypesToMatch=" + typesStr +
                              ", token=" + (token ? token->toString() : "nullptr") +
                              ", current = " + std::to_string(current));

    return false;
}

}  // namespace

Parser::Parser(std::vector<std::shared_ptr<IToken>> tokens) : m_tokens(std::move(tokens))
{
    Logger::getInstance().log(" [Parser][Parser] Constructed with m_tokens.size()=" +
                              std::to_string(m_tokens.size()));
}

bool Parser::check(const TokenType type) const
{
    std::shared_ptr<IToken> token = peekCurrentToken();
    Logger::getInstance().log(" [Parser][check] Token" + token->toString() +
                              " -> Type=" + TokenTypeNameSpace::toString(type) +
                              ", m_current=" + std::to_string(m_current));

    if (isAtEnd(token)) return false;
    auto placeholder = token->getTypeEnum() == type;

    Logger::getInstance().log(" [Parser][check] Checking token type: " +
                              TokenTypeNameSpace::toString(token->getTypeEnum()) +
                              " against expected type: " + TokenTypeNameSpace::toString(type) +
                              " Result : " + std::to_string(placeholder));
    return placeholder;
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
    if (tokenIndex < 0 || tokenIndex >= static_cast<int>(m_tokens.size())) return nullptr;
    return ::peek(m_tokens, tokenIndex);
}

std::shared_ptr<IToken> Parser::peekCurrentToken() const  // Private
{
    Logger::getInstance().log(" [Parser][peekCurrentToken] m_current=" + std::to_string(m_current));
    if (m_current < 0 || m_current >= static_cast<int>(m_tokens.size()))
    {
        auto message = "Parse Error: m_current out of bounds in peekCurrentToken. m_current=" +
                       std::to_string(m_current) +
                       ", m_tokens.size()=" + std::to_string(m_tokens.size());
        Logger::getInstance().log(" [Parser][peekCurrentToken] " + message);
        // throw runtime_error(message);
    }
    // Return the current token without consuming it
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

std::shared_ptr<IToken> Parser::consume(TokenType type, const std::string& message)
{
    Logger::getInstance().log(" [Parser][consume] type=" + TokenTypeNameSpace::toString(type) +
                              ", m_current=" + std::to_string(m_current));
    auto currentToken = peekCurrentToken();
    if (!currentToken) error(currentToken, "Unexpected end of input.");
    if (check(type))
    {
        Logger::getInstance().log(" [Parser][consume] Consumed token: " + currentToken->toString());
        return advance();
    }

    Logger::getInstance().log(" [Parser][consume] Error: Expected token type " +
                              TokenTypeNameSpace::toString(type) + ", but found " +
                              currentToken->toString() + ". Message: " + message);
    error(currentToken, message);
}

void Parser::error(std::shared_ptr<IToken> token, const std::string& message)
{
    Logger::getInstance().log(" [Parser][error] token=" + (token ? token->toString() : "nullptr") +
                              ", message=" + message);

    if (token == nullptr)
    {
        throw runtime_error("Parse Error at nullptr: " + message);
    }
    else if (token->getTypeEnum() == TokenType::END_OF_FILE)
    {
        throw runtime_error("Parse Error at end: " + message);
    }
    else
    {
        throw runtime_error("Parse Error at " + token->toString() + ": " + message);
    }
}

std::shared_ptr<CommonParserType> Parser::parse()
{
    Logger::getInstance().log(" [Parser][parse] m_current=" + std::to_string(m_current));
    try
    {
        if (match({TokenType::CLASS}, peekCurrentToken(), m_current))
        {
            Logger::getInstance().log(" [Parser][parse] Class token found, parsing class.");
            return classDeclaration();
        }
        else
        {
            return expression();
        }
    }
    catch (const std::runtime_error& e)
    {
        Logger::getInstance().log(" [Parser][parse] Exception: " + std::string(e.what()));
        throw runtime_error("Parse Error: " + std::string(e.what()));
    }
}

std::shared_ptr<ClassST> Parser::classDeclaration()
{
    Logger::getInstance().log(" [Parser][classDeclaration] m_current=" + std::to_string(m_current));
    // Placeholder for class declaration parsing logic
    // This should parse class declarations and return a Class object

    auto classNameIdentifier = consume(TokenType::IDENTIFIER, "Expect class name.");

    // TODO: HANGTO CLASS STORAGE INSTEAD OF TOKEN
    std::vector<std::shared_ptr<IToken>> parentClassTokens;

    // TODO: Add the class name and the inherency classes
    if (match({TokenType::COLON}, peekCurrentToken(), m_current))
    {
        Logger::getInstance().log(" [Parser][classDeclaration] Found inheritance structure.");

        auto previousToken = previous();
        auto currentToken = peekCurrentToken();

        Logger::getInstance().log(
            "[Parser][classDeclaration] previousToken->getTypeEnum() : " +
            TokenTypeNameSpace::toString(previousToken->getTypeEnum()) +
            " currentToken: " + currentToken->toString() +
            " Result: " + std::to_string((previousToken->getTypeEnum() != TokenType::COLON)));

        while (match({TokenType::COMMA}, peekCurrentToken(), m_current) ||
               (previous()->getTypeEnum() == TokenType::COLON))
        {
            Logger::getInstance().log(" [Parser][classDeclaration] Found parent class.");

            if (match({TokenType::PUBLIC, TokenType::PROTECTED, TokenType::PRIVATE},
                      peekCurrentToken(), m_current))
            {
                Logger::getInstance().log(
                    " [Parser][classDeclaration] Parent class access type found.");
                // Consume the access type token
                auto parentClassAccessType = previous();
                auto parentClassName = consume(TokenType::IDENTIFIER, "Expect class name.");

                Logger::getInstance().log(" [Parser][classDeclaration] Parent class access type: " +
                                          parentClassAccessType->toString() +
                                          ", Parent class name: " + parentClassName->toString());

                parentClassTokens.push_back(parentClassAccessType);
                parentClassTokens.push_back(parentClassName);
            }
            else
            {
                error(currentToken, "Expect access type for parent class.");
            }
        }
    }

    // TODO: Add the list of tokens to the statement property
    if (match({TokenType::LEFT_BRACE}, peekCurrentToken(), m_current))
    {
        Logger::getInstance().log(" [Parser][classDeclaration] Class body found.");
        // Here we would parse the class body, but for now, we just consume it.
        while (!isAtEnd(peekCurrentToken()))
        {
            if (match({TokenType::RIGHT_BRACE}, peekCurrentToken(), m_current)) break;
            advance();  // Consume tokens until we find the right brace
        }
        auto previousToken = previous();
        Logger::getInstance().log(
            "[Parser][ClassDeclaraton] previousToken->getTypeEnum() : " +
            TokenTypeNameSpace::toString(previousToken->getTypeEnum()) +
            " Result: " + std::to_string((previousToken->getTypeEnum() != TokenType::RIGHT_BRACE)));
        if (previousToken && previousToken->getTypeEnum() != TokenType::RIGHT_BRACE)
        {
            error(previousToken, "Expect '}' in the end of the class body statement.");
        }
    }

    return nullptr;  // Replace with actual implementation
}

// ----------------- grammar functions -----------------

std::shared_ptr<Expression> Parser::expression()
{
    Logger::getInstance().log(" [Parser][expression] m_current=" + std::to_string(m_current));

    if (isAtEnd(peekCurrentToken()))
    {
        Logger::getInstance().log(" [Parser][expression] No tokens to parse, returning nullptr.");
        return nullptr;
    }

    return equality();
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
        auto right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken);
    }
    return expr;
}

std::shared_ptr<Expression> Parser::comparison()
{
    Logger::getInstance().log(" [Parser][comparison] m_current=" + std::to_string(m_current));
    auto expr = term();

    while (match(
        {TokenType::LESS, TokenType::GREATER, TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL},
        peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        Logger::getInstance().log(" [Parser][comparison] operatorToken=" +
                                  (operatorToken ? operatorToken->toString() : "nullptr"));
        auto right = comparison();
        expr = std::make_shared<BinaryExpression>(expr, right, operatorToken);
    }
    return expr;
}

std::shared_ptr<Expression> Parser::term()
{
    Logger::getInstance().log(" [Parser][term] m_current=" + std::to_string(m_current));
    auto expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS}, peekCurrentToken(), m_current))
    {
        auto operatorToken = previous();
        Logger::getInstance().log(" [Parser][term] operatorToken=" +
                                  (operatorToken ? operatorToken->toString() : "nullptr"));
        auto right = comparison();
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
        auto right = comparison();
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
        auto right = unary();
        return std::make_shared<UnaryExpression>(operatorToken, right);
    }
    return primary();
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
    if (match({TokenType::IDENTIFIER}, currentToken, m_current))
        return std::make_shared<LiteralExpression>(currentToken);

    if (match({TokenType::LEFT_PAREN}, currentToken, m_current))
    {
        Logger::getInstance().log(" [Parser][primary] Grouping expression found.");
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        Logger::getInstance().log(" [Parser][primary] Returning GroupingExpression.");
        return std::make_shared<GroupingExpression>(expr);
    }

    error(currentToken, "Expect expression.");
    return nullptr;
}
