#pragma once

// If added new type, remember to update the `toString` function below.

#include <string>
#include <unordered_map>
enum class TokenType
{
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    COLON,
    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,
    // Keywords.
    ALIGNAS,
    ALIGNOF,
    AND,
    AND_EQ,
    ASM,
    AUTO,
    BITAND,
    BITOR,
    BOOL,
    BREAK,
    CASE,
    CATCH,
    CHAR,
    CHAR8_T,
    CHAR16_T,
    CHAR32_T,
    CLASS,
    COMPL,
    CONCEPT,
    CONST,
    CONSTEVAL,
    CONSTEXPR,
    CONSTINIT,
    CONST_CAST,
    CONTINUE,
    CO_AWAIT,
    CO_RETURN,
    CO_YIELD,
    DECLTYPE,
    DEFAULT,
    DELETE,
    DO,
    DOUBLE,
    DYNAMIC_CAST,
    ELSE,
    ENUM,
    EXPLICIT,
    EXPORT,
    EXTERN,
    FALSE,
    FLOAT,
    FOR,
    FRIEND,
    GOTO,
    IF,
    INLINE,
    INT,
    LONG,
    MUTABLE,
    NAMESPACE,
    NEW,
    NOEXCEPT,
    NOT,
    NOT_EQ,
    NULLPTR,
    OPERATOR,
    OR,
    OR_EQ,
    PRIVATE,
    PROTECTED,
    PUBLIC,
    REGISTER,
    REINTERPRET_CAST,
    REQUIRES,
    RETURN,
    SHORT,
    SIGNED,
    SIZEOF,
    STATIC,
    STATIC_ASSERT,
    STATIC_CAST,
    STRUCT,
    SWITCH,
    TEMPLATE,
    THIS,
    THREAD_LOCAL,
    THROW,
    TRUE,
    TRY,
    TYPEDEF,
    TYPEID,
    TYPENAME,
    UNION,
    UNSIGNED,
    USING,
    VIRTUAL,
    VOID,
    VOLATILE,
    WCHAR_T,
    WHILE,
    XOR,
    XOR_EQ,
    // Not Defined
    UNKNOWN,
    END_OF_FILE
};

namespace TokenTypeNameSpace
{
inline std::string toString(TokenType type)
{
    switch (type)
    {
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::DOT:
            return "DOT";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::SEMICOLON:
            return "SEMICOLON";
        case TokenType::COLON:
            return "COLON";
        case TokenType::SLASH:
            return "SLASH";
        case TokenType::STAR:
            return "STAR";
        case TokenType::BANG:
            return "BANG";
        case TokenType::BANG_EQUAL:
            return "BANG_EQUAL";
        case TokenType::EQUAL:
            return "EQUAL";
        case TokenType::EQUAL_EQUAL:
            return "EQUAL_EQUAL";
        case TokenType::GREATER:
            return "GREATER";
        case TokenType::GREATER_EQUAL:
            return "GREATER_EQUAL";
        case TokenType::LESS:
            return "LESS";
        case TokenType::LESS_EQUAL:
            return "LESS_EQUAL";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::STRING:
            return "STRING";
        case TokenType::NUMBER:
            return "NUMBER";
        case TokenType::AND:
            return "AND";
        case TokenType::CLASS:
            return "CLASS";
        case TokenType::ELSE:
            return "ELSE";
        case TokenType::FALSE:
            return "FALSE";
        case TokenType::FOR:
            return "FOR";
        case TokenType::IF:
            return "IF";
        case TokenType::OR:
            return "OR";
        case TokenType::RETURN:
            return "RETURN";
        case TokenType::THIS:
            return "THIS";
        case TokenType::TRUE:
            return "TRUE";
        case TokenType::WHILE:
            return "WHILE";
        case TokenType::VOID:
            return "VOID";
        case TokenType::DELETE:
            return "DELETE";
        case TokenType::NEW:
            return "NEW";
        case TokenType::PROTECTED:
            return "PROTECTED";
        case TokenType::ALIGNAS:
            return "ALIGNAS";
        case TokenType::ALIGNOF:
            return "ALIGNOF";
        case TokenType::AND_EQ:
            return "AND_EQ";
        case TokenType::ASM:
            return "ASM";
        case TokenType::AUTO:
            return "AUTO";
        case TokenType::BITAND:
            return "BITAND";
        case TokenType::BITOR:
            return "BITOR";
        case TokenType::BOOL:
            return "BOOL";
        case TokenType::BREAK:
            return "BREAK";
        case TokenType::CASE:
            return "CASE";
        case TokenType::CATCH:
            return "CATCH";
        case TokenType::CHAR:
            return "CHAR";
        case TokenType::CHAR8_T:
            return "CHAR8_T";
        case TokenType::CHAR16_T:
            return "CHAR16_T";
        case TokenType::CHAR32_T:
            return "CHAR32_T";
        case TokenType::COMPL:
            return "COMPL";
        case TokenType::CONCEPT:
            return "CONCEPT";
        case TokenType::CONST:
            return "CONST";
        case TokenType::CONSTEVAL:
            return "CONSTEVAL";
        case TokenType::CONSTEXPR:
            return "CONSTEXPR";
        case TokenType::CONSTINIT:
            return "CONSTINIT";
        case TokenType::CONST_CAST:
            return "CONST_CAST";
        case TokenType::CONTINUE:
            return "CONTINUE";
        case TokenType::CO_AWAIT:
            return "CO_AWAIT";
        case TokenType::CO_RETURN:
            return "CO_RETURN";
        case TokenType::CO_YIELD:
            return "CO_YIELD";
        case TokenType::DECLTYPE:
            return "DECLTYPE";
        case TokenType::DEFAULT:
            return "DEFAULT";
        case TokenType::DO:
            return "DO";
        case TokenType::DOUBLE:
            return "DOUBLE";
        case TokenType::DYNAMIC_CAST:
            return "DYNAMIC_CAST";
        case TokenType::ENUM:
            return "ENUM";
        case TokenType::EXPLICIT:
            return "EXPLICIT";
        case TokenType::EXPORT:
            return "EXPORT";
        case TokenType::EXTERN:
            return "EXTERN";
        case TokenType::FLOAT:
            return "FLOAT";
        case TokenType::FRIEND:
            return "FRIEND";
        case TokenType::GOTO:
            return "GOTO";
        case TokenType::INLINE:
            return "INLINE";
        case TokenType::INT:
            return "INT";
        case TokenType::LONG:
            return "LONG";
        case TokenType::MUTABLE:
            return "MUTABLE";
        case TokenType::NAMESPACE:
            return "NAMESPACE";
        case TokenType::NOEXCEPT:
            return "NOEXCEPT";
        case TokenType::NOT:
            return "NOT";
        case TokenType::NOT_EQ:
            return "NOT_EQ";
        case TokenType::NULLPTR:
            return "NULLPTR";
        case TokenType::OPERATOR:
            return "OPERATOR";
        case TokenType::OR_EQ:
            return "OR_EQ";
        case TokenType::PRIVATE:
            return "PRIVATE";
        case TokenType::PUBLIC:
            return "PUBLIC";
        case TokenType::REGISTER:
            return "REGISTER";
        case TokenType::REINTERPRET_CAST:
            return "REINTERPRET_CAST";
        case TokenType::REQUIRES:
            return "REQUIRES";
        case TokenType::SHORT:
            return "SHORT";
        case TokenType::SIGNED:
            return "SIGNED";
        case TokenType::SIZEOF:
            return "SIZEOF";
        case TokenType::STATIC:
            return "STATIC";
        case TokenType::STATIC_ASSERT:
            return "STATIC_ASSERT";
        case TokenType::STATIC_CAST:
            return "STATIC_CAST";
        case TokenType::STRUCT:
            return "STRUCT";
        case TokenType::SWITCH:
            return "SWITCH";
        case TokenType::TEMPLATE:
            return "TEMPLATE";
        case TokenType::THREAD_LOCAL:
            return "THREAD_LOCAL";
        case TokenType::THROW:
            return "THROW";
        case TokenType::TRY:
            return "TRY";
        case TokenType::TYPEDEF:
            return "TYPEDEF";
        case TokenType::TYPEID:
            return "TYPEID";
        case TokenType::TYPENAME:
            return "TYPENAME";
        case TokenType::UNION:
            return "UNION";
        case TokenType::UNSIGNED:
            return "UNSIGNED";
        case TokenType::USING:
            return "USING";
        case TokenType::VIRTUAL:
            return "VIRTUAL";
        case TokenType::VOLATILE:
            return "VOLATILE";
        case TokenType::WCHAR_T:
            return "WCHAR_T";
        case TokenType::XOR:
            return "XOR";
        case TokenType::XOR_EQ:
            return "XOR_EQ";
        case TokenType::END_OF_FILE:
            return "END_OF_FILE";
        default:
            return "UNKNOWN";
    }
}

static std::unordered_map<std::string, TokenType> keywordsMap = {
    {"and", TokenType::AND},
    {"and_eq", TokenType::AND_EQ},
    {"asm", TokenType::ASM},
    {"auto", TokenType::AUTO},
    {"bitand", TokenType::BITAND},
    {"bitor", TokenType::BITOR},
    {"bool", TokenType::BOOL},
    {"break", TokenType::BREAK},
    {"case", TokenType::CASE},
    {"catch", TokenType::CATCH},
    {"char", TokenType::CHAR},
    {"char8_t", TokenType::CHAR8_T},
    {"char16_t", TokenType::CHAR16_T},
    {"char32_t", TokenType::CHAR32_T},
    {"class", TokenType::CLASS},
    {"compl", TokenType::COMPL},
    {"concept", TokenType::CONCEPT},
    {"const", TokenType::CONST},
    {"consteval", TokenType::CONSTEVAL},
    {"constexpr", TokenType::CONSTEXPR},
    {"constinit", TokenType::CONSTINIT},
    {"const_cast", TokenType::CONST_CAST},
    {"continue", TokenType::CONTINUE},
    {"co_await", TokenType::CO_AWAIT},
    {"co_return", TokenType::CO_RETURN},
    {"co_yield", TokenType::CO_YIELD},
    {"decltype", TokenType::DECLTYPE},
    {"default", TokenType::DEFAULT},
    {"delete", TokenType::DELETE},
    {"do", TokenType::DO},
    {"double", TokenType::DOUBLE},
    {"dynamic_cast", TokenType::DYNAMIC_CAST},
    {"else", TokenType::ELSE},
    {"enum", TokenType::ENUM},
    {"explicit", TokenType::EXPLICIT},
    {"export", TokenType::EXPORT},
    {"extern", TokenType::EXTERN},
    {"false", TokenType::FALSE},
    {"float", TokenType::FLOAT},
    {"for", TokenType::FOR},
    {"friend", TokenType::FRIEND},
    {"goto", TokenType::GOTO},
    {"if", TokenType::IF},
    {"inline", TokenType::INLINE},
    {"int", TokenType::INT},
    {"long", TokenType::LONG},
    {"mutable", TokenType::MUTABLE},
    {"namespace", TokenType::NAMESPACE},
    {"new", TokenType::NEW},
    {"noexcept", TokenType::NOEXCEPT},
    {"nullptr", TokenType::NULLPTR},
    {"operator", TokenType::OPERATOR},
    {"or", TokenType::OR},
    {"or_eq", TokenType::OR_EQ},
    {"private", TokenType::PRIVATE},
    {"protected", TokenType::PROTECTED},
    {"public", TokenType::PUBLIC},
    {"register", TokenType::REGISTER},
    {"reinterpret_cast", TokenType::REINTERPRET_CAST},
    {"requires", TokenType::REQUIRES},
    {"return", TokenType::RETURN},
    {"short", TokenType::SHORT},
    {"signed", TokenType::SIGNED},
    {"sizeof", TokenType::SIZEOF},
    {"static", TokenType::STATIC},
    {"static_assert", TokenType::STATIC_ASSERT},
    {"static_cast", TokenType::STATIC_CAST},
    {"struct", TokenType::STRUCT},
    {"switch", TokenType::SWITCH},
    {"template", TokenType::TEMPLATE},
    {"this", TokenType::THIS},
    {"thread_local", TokenType::THREAD_LOCAL},
    {"throw", TokenType::THROW},
    {"true", TokenType::TRUE},
    {"try", TokenType::TRY},
    {"typedef", TokenType::TYPEDEF},
    {"typeid", TokenType::TYPEID},
    {"typename", TokenType::TYPENAME},
    {"union", TokenType::UNION},
    {"unsigned", TokenType::UNSIGNED},
    {"using", TokenType::USING},
    {"virtual", TokenType::VIRTUAL},
    {"void", TokenType::VOID},
    {"volatile", TokenType::VOLATILE},
    {"wchar_t", TokenType::WCHAR_T},
    {"while", TokenType::WHILE},
    {"xor", TokenType::XOR},
    {"xor_eq", TokenType::XOR_EQ},
    {"end_of_file", TokenType::END_OF_FILE}};
}  // namespace TokenTypeNameSpace
