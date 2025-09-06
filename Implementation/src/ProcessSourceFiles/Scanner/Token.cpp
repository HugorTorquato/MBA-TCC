#include "Token.h"

#include "../../Logger/Log.h"
#include "TokenType.h"

Token::Token(TokenType type, const std::string& lexeme, const LineFile& lineFile)
    : m_type(type), m_lexeme(lexeme), m_lineFile(lineFile)
{
    if (lexeme.empty() && type != TokenType::END_OF_FILE)
    {
        m_type = TokenType::UNKNOWN;
    }

    Logger::getInstance().log(toString());
}

std::string Token::getType() const
{
    return TokenTypeNameSpace::toString(m_type);
}

TokenType Token::getTypeEnum() const
{
    return m_type;
}
std::string Token::getLexeme() const
{
    return m_lexeme;
}

std::string Token::getLineFile() const
{
    return m_lineFile.getLineFileAsString();
}

LineFile Token::getLineFileObj() const
{
    return m_lineFile;
}

std::string Token::toString() const
{
    return "Token Type: " + TokenTypeNameSpace::toString(m_type) + ", Lexeme: " + m_lexeme +
           ", LineFile: " + m_lineFile.getLineFileAsString();
}
