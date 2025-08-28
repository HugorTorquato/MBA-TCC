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
            "[ClassST::ClassST] Token is not an IDENTIFIER, can't create CLASS object. Token : " +
            classToken->toString();
        Logger::getInstance().log(message);
        throw std::runtime_error(message);
    }

    m_className = classToken->getLexeme();
    m_classToken = classToken;
}

std::string ClassST::getClassName() const
{
    return m_className;
}

std::shared_ptr<IToken> ClassST::getClassToken() const
{
    return m_classToken;
}

std::vector<ClassST::baseClassPair> ClassST::getInherencyArray() const
{
    return m_inherencyArray;
}

void ClassST::addInherencyToClassObject(std::shared_ptr<IToken> accessType,
                                        std::shared_ptr<IToken> className)
{
    if (accessType->getTypeEnum() != TokenType::PUBLIC &&
        accessType->getTypeEnum() != TokenType::PRIVATE &&
        accessType->getTypeEnum() != TokenType::PROTECTED)
    {
        auto message =
            "[ClassST::addInherencyToClassObject][] Access type is not valid, can't "
            "add to inherency array. Access Type : " +
            accessType->toString();
        Logger::getInstance().log(message);
        throw std::runtime_error(message);
    }

    if (className->getTypeEnum() != TokenType::IDENTIFIER)
    {
        auto message =
            "[ClassST::addInherencyToClassObject][] Class name is not an IDENTIFIER, "
            "can't add to inherency array. Class Name : " +
            className->toString();
        Logger::getInstance().log(message);
        throw std::runtime_error(message);
    }

    baseClassPair basClassToAdd = std::make_pair(accessType, className);
    Logger::getInstance().log(
        "[ClassST::addInherencyToClassObject] Adding base class to inherency array: " +
        basClassToAdd.first->toString() + ", " + basClassToAdd.second->toString());

    m_inherencyArray.emplace_back(basClassToAdd);
}

bool ClassST::hasBaseClasses() const
{
    return !m_inherencyArray.empty();
}

std::string ClassST::toString() const
{
    // TODO: Ad the list of children in a filestream and append to the return
    return "[ClassST] Class name: " + m_className;
}