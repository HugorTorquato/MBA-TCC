#pragma once

#include "IToken.h"

class Token : public IToken
{
   public:
    Token() = default;
//     Token(const std::string& type, const std::string& lexeme, int line)
//         : m_type(type), m_lexeme(lexeme), m_line(line) {}

//     std::string getType() const { return m_type; }
//     std::string getLexeme() const { return m_lexeme; }
//     int getLine() const { return m_line; }

//    private:
//     std::string m_type;
//     std::string m_lexeme;
//     int m_line;
};