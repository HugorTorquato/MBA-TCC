#include "ClassST.h"

#include <stdexcept>

#include "../../Logger/Log.h"

ClassST::ClassST(const std::string& className) : m_className(className) {}

ClassST::ClassST(std::shared_ptr<IToken> classToken)
{
    if (classToken->getTypeEnum() != TokenType::IDENTIFIER)
    {
        // If emtpy lexeme, the TOKEN logic will add an TokenType::UNKNOWN type
        auto message =
            "[ClassST::ClassST][] Token is not an IDENTIFIER, can't create CLASS object. Token : " +
            classToken->toString();
        Logger::getInstance().log(message);
        throw std::runtime_error(message);
    }

    m_className = classToken->getLexeme();
}

std::string ClassST::getClassName() const
{
    return m_className;
}