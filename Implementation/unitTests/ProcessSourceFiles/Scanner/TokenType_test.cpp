#include "../../../src/ProcessSourceFiles/Scanner/TokenType.h"

#include <gtest/gtest.h>

#include <set>

class TokenTypeTest : public ::testing::Test
{
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(TokenTypeTest, ToString_ReturnsCorrectString)
{
    using namespace TokenTypeNameSpace;
    // Test all enum values for toString
    EXPECT_EQ(toString(TokenType::LEFT_PAREN), "LEFT_PAREN");
    EXPECT_EQ(toString(TokenType::RIGHT_PAREN), "RIGHT_PAREN");
    EXPECT_EQ(toString(TokenType::LEFT_BRACE), "LEFT_BRACE");
    EXPECT_EQ(toString(TokenType::RIGHT_BRACE), "RIGHT_BRACE");
    EXPECT_EQ(toString(TokenType::COMMA), "COMMA");
    EXPECT_EQ(toString(TokenType::DOT), "DOT");
    EXPECT_EQ(toString(TokenType::MINUS), "MINUS");
    EXPECT_EQ(toString(TokenType::PLUS), "PLUS");
    EXPECT_EQ(toString(TokenType::SEMICOLON), "SEMICOLON");
    EXPECT_EQ(toString(TokenType::SLASH), "SLASH");
    EXPECT_EQ(toString(TokenType::STAR), "STAR");
    EXPECT_EQ(toString(TokenType::BANG), "BANG");
    EXPECT_EQ(toString(TokenType::BANG_EQUAL), "BANG_EQUAL");
    EXPECT_EQ(toString(TokenType::EQUAL), "EQUAL");
    EXPECT_EQ(toString(TokenType::EQUAL_EQUAL), "EQUAL_EQUAL");
    EXPECT_EQ(toString(TokenType::GREATER), "GREATER");
    EXPECT_EQ(toString(TokenType::GREATER_EQUAL), "GREATER_EQUAL");
    EXPECT_EQ(toString(TokenType::LESS), "LESS");
    EXPECT_EQ(toString(TokenType::LESS_EQUAL), "LESS_EQUAL");
    EXPECT_EQ(toString(TokenType::IDENTIFIER), "IDENTIFIER");
    EXPECT_EQ(toString(TokenType::STRING), "STRING");
    EXPECT_EQ(toString(TokenType::NUMBER), "NUMBER");
    EXPECT_EQ(toString(TokenType::AND), "AND");
    EXPECT_EQ(toString(TokenType::AND_EQ), "AND_EQ");
    EXPECT_EQ(toString(TokenType::ASM), "ASM");
    EXPECT_EQ(toString(TokenType::AUTO), "AUTO");
    EXPECT_EQ(toString(TokenType::BITAND), "BITAND");
    EXPECT_EQ(toString(TokenType::BITOR), "BITOR");
    EXPECT_EQ(toString(TokenType::BOOL), "BOOL");
    EXPECT_EQ(toString(TokenType::BREAK), "BREAK");
    EXPECT_EQ(toString(TokenType::CASE), "CASE");
    EXPECT_EQ(toString(TokenType::CATCH), "CATCH");
    EXPECT_EQ(toString(TokenType::CHAR), "CHAR");
    EXPECT_EQ(toString(TokenType::CHAR8_T), "CHAR8_T");
    EXPECT_EQ(toString(TokenType::CHAR16_T), "CHAR16_T");
    EXPECT_EQ(toString(TokenType::CHAR32_T), "CHAR32_T");
    EXPECT_EQ(toString(TokenType::CLASS), "CLASS");
    EXPECT_EQ(toString(TokenType::COMPL), "COMPL");
    EXPECT_EQ(toString(TokenType::CONCEPT), "CONCEPT");
    EXPECT_EQ(toString(TokenType::CONST), "CONST");
    EXPECT_EQ(toString(TokenType::CONSTEVAL), "CONSTEVAL");
    EXPECT_EQ(toString(TokenType::CONSTEXPR), "CONSTEXPR");
    EXPECT_EQ(toString(TokenType::CONSTINIT), "CONSTINIT");
    EXPECT_EQ(toString(TokenType::CONST_CAST), "CONST_CAST");
    EXPECT_EQ(toString(TokenType::CONTINUE), "CONTINUE");
    EXPECT_EQ(toString(TokenType::CO_AWAIT), "CO_AWAIT");
    EXPECT_EQ(toString(TokenType::CO_RETURN), "CO_RETURN");
    EXPECT_EQ(toString(TokenType::CO_YIELD), "CO_YIELD");
    EXPECT_EQ(toString(TokenType::DECLTYPE), "DECLTYPE");
    EXPECT_EQ(toString(TokenType::DEFAULT), "DEFAULT");
    EXPECT_EQ(toString(TokenType::DELETE), "DELETE");
    EXPECT_EQ(toString(TokenType::DO), "DO");
    EXPECT_EQ(toString(TokenType::DOUBLE), "DOUBLE");
    EXPECT_EQ(toString(TokenType::DYNAMIC_CAST), "DYNAMIC_CAST");
    EXPECT_EQ(toString(TokenType::ELSE), "ELSE");
    EXPECT_EQ(toString(TokenType::ENUM), "ENUM");
    EXPECT_EQ(toString(TokenType::EXPLICIT), "EXPLICIT");
    EXPECT_EQ(toString(TokenType::EXPORT), "EXPORT");
    EXPECT_EQ(toString(TokenType::EXTERN), "EXTERN");
    EXPECT_EQ(toString(TokenType::FALSE), "FALSE");
    EXPECT_EQ(toString(TokenType::FLOAT), "FLOAT");
    EXPECT_EQ(toString(TokenType::FOR), "FOR");
    EXPECT_EQ(toString(TokenType::FRIEND), "FRIEND");
    EXPECT_EQ(toString(TokenType::GOTO), "GOTO");
    EXPECT_EQ(toString(TokenType::IF), "IF");
    EXPECT_EQ(toString(TokenType::INLINE), "INLINE");
    EXPECT_EQ(toString(TokenType::INT), "INT");
    EXPECT_EQ(toString(TokenType::LONG), "LONG");
    EXPECT_EQ(toString(TokenType::MUTABLE), "MUTABLE");
    EXPECT_EQ(toString(TokenType::NAMESPACE), "NAMESPACE");
    EXPECT_EQ(toString(TokenType::NEW), "NEW");
    EXPECT_EQ(toString(TokenType::NOEXCEPT), "NOEXCEPT");
    EXPECT_EQ(toString(TokenType::NOT), "NOT");
    EXPECT_EQ(toString(TokenType::NOT_EQ), "NOT_EQ");
    EXPECT_EQ(toString(TokenType::NULLPTR), "NULLPTR");
    EXPECT_EQ(toString(TokenType::OPERATOR), "OPERATOR");
    EXPECT_EQ(toString(TokenType::OR), "OR");
    EXPECT_EQ(toString(TokenType::OR_EQ), "OR_EQ");
    EXPECT_EQ(toString(TokenType::PRIVATE), "PRIVATE");
    EXPECT_EQ(toString(TokenType::PROTECTED), "PROTECTED");
    EXPECT_EQ(toString(TokenType::PUBLIC), "PUBLIC");
    EXPECT_EQ(toString(TokenType::REGISTER), "REGISTER");
    EXPECT_EQ(toString(TokenType::REINTERPRET_CAST), "REINTERPRET_CAST");
    EXPECT_EQ(toString(TokenType::REQUIRES), "REQUIRES");
    EXPECT_EQ(toString(TokenType::RETURN), "RETURN");
    EXPECT_EQ(toString(TokenType::SHORT), "SHORT");
    EXPECT_EQ(toString(TokenType::SIGNED), "SIGNED");
    EXPECT_EQ(toString(TokenType::SIZEOF), "SIZEOF");
    EXPECT_EQ(toString(TokenType::STATIC), "STATIC");
    EXPECT_EQ(toString(TokenType::STATIC_ASSERT), "STATIC_ASSERT");
    EXPECT_EQ(toString(TokenType::STATIC_CAST), "STATIC_CAST");
    EXPECT_EQ(toString(TokenType::STRUCT), "STRUCT");
    EXPECT_EQ(toString(TokenType::SWITCH), "SWITCH");
    EXPECT_EQ(toString(TokenType::TEMPLATE), "TEMPLATE");
    EXPECT_EQ(toString(TokenType::THIS), "THIS");
    EXPECT_EQ(toString(TokenType::THREAD_LOCAL), "THREAD_LOCAL");
    EXPECT_EQ(toString(TokenType::THROW), "THROW");
    EXPECT_EQ(toString(TokenType::TRUE), "TRUE");
    EXPECT_EQ(toString(TokenType::TRY), "TRY");
    EXPECT_EQ(toString(TokenType::TYPEDEF), "TYPEDEF");
    EXPECT_EQ(toString(TokenType::TYPEID), "TYPEID");
    EXPECT_EQ(toString(TokenType::TYPENAME), "TYPENAME");
    EXPECT_EQ(toString(TokenType::UNION), "UNION");
    EXPECT_EQ(toString(TokenType::UNSIGNED), "UNSIGNED");
    EXPECT_EQ(toString(TokenType::USING), "USING");
    EXPECT_EQ(toString(TokenType::VIRTUAL), "VIRTUAL");
    EXPECT_EQ(toString(TokenType::VOID), "VOID");
    EXPECT_EQ(toString(TokenType::VOLATILE), "VOLATILE");
    EXPECT_EQ(toString(TokenType::WCHAR_T), "WCHAR_T");
    EXPECT_EQ(toString(TokenType::WHILE), "WHILE");
    EXPECT_EQ(toString(TokenType::XOR), "XOR");
    EXPECT_EQ(toString(TokenType::XOR_EQ), "XOR_EQ");
    EXPECT_EQ(toString(TokenType::UNKNOWN), "UNKNOWN");
}

TEST_F(TokenTypeTest, EvaluateKeyWordsMapOptions)
{
    using namespace TokenTypeNameSpace;
    // Check that every keyword in the map maps to the correct TokenType
    EXPECT_EQ(keywordsMap.at("and"), TokenType::AND);
    EXPECT_EQ(keywordsMap.at("and_eq"), TokenType::AND_EQ);
    EXPECT_EQ(keywordsMap.at("asm"), TokenType::ASM);
    EXPECT_EQ(keywordsMap.at("auto"), TokenType::AUTO);
    EXPECT_EQ(keywordsMap.at("bitand"), TokenType::BITAND);
    EXPECT_EQ(keywordsMap.at("bitor"), TokenType::BITOR);
    EXPECT_EQ(keywordsMap.at("bool"), TokenType::BOOL);
    EXPECT_EQ(keywordsMap.at("break"), TokenType::BREAK);
    EXPECT_EQ(keywordsMap.at("case"), TokenType::CASE);
    EXPECT_EQ(keywordsMap.at("catch"), TokenType::CATCH);
    EXPECT_EQ(keywordsMap.at("char"), TokenType::CHAR);
    EXPECT_EQ(keywordsMap.at("char8_t"), TokenType::CHAR8_T);
    EXPECT_EQ(keywordsMap.at("char16_t"), TokenType::CHAR16_T);
    EXPECT_EQ(keywordsMap.at("char32_t"), TokenType::CHAR32_T);
    EXPECT_EQ(keywordsMap.at("class"), TokenType::CLASS);
    EXPECT_EQ(keywordsMap.at("compl"), TokenType::COMPL);
    EXPECT_EQ(keywordsMap.at("concept"), TokenType::CONCEPT);
    EXPECT_EQ(keywordsMap.at("const"), TokenType::CONST);
    EXPECT_EQ(keywordsMap.at("consteval"), TokenType::CONSTEVAL);
    EXPECT_EQ(keywordsMap.at("constexpr"), TokenType::CONSTEXPR);
    EXPECT_EQ(keywordsMap.at("constinit"), TokenType::CONSTINIT);
    EXPECT_EQ(keywordsMap.at("const_cast"), TokenType::CONST_CAST);
    EXPECT_EQ(keywordsMap.at("continue"), TokenType::CONTINUE);
    EXPECT_EQ(keywordsMap.at("co_await"), TokenType::CO_AWAIT);
    EXPECT_EQ(keywordsMap.at("co_return"), TokenType::CO_RETURN);
    EXPECT_EQ(keywordsMap.at("co_yield"), TokenType::CO_YIELD);
    EXPECT_EQ(keywordsMap.at("decltype"), TokenType::DECLTYPE);
    EXPECT_EQ(keywordsMap.at("default"), TokenType::DEFAULT);
    EXPECT_EQ(keywordsMap.at("delete"), TokenType::DELETE);
    EXPECT_EQ(keywordsMap.at("do"), TokenType::DO);
    EXPECT_EQ(keywordsMap.at("double"), TokenType::DOUBLE);
    EXPECT_EQ(keywordsMap.at("dynamic_cast"), TokenType::DYNAMIC_CAST);
    EXPECT_EQ(keywordsMap.at("else"), TokenType::ELSE);
    EXPECT_EQ(keywordsMap.at("enum"), TokenType::ENUM);
    EXPECT_EQ(keywordsMap.at("explicit"), TokenType::EXPLICIT);
    EXPECT_EQ(keywordsMap.at("export"), TokenType::EXPORT);
    EXPECT_EQ(keywordsMap.at("extern"), TokenType::EXTERN);
    EXPECT_EQ(keywordsMap.at("false"), TokenType::FALSE);
    EXPECT_EQ(keywordsMap.at("float"), TokenType::FLOAT);
    EXPECT_EQ(keywordsMap.at("for"), TokenType::FOR);
    EXPECT_EQ(keywordsMap.at("friend"), TokenType::FRIEND);
    EXPECT_EQ(keywordsMap.at("goto"), TokenType::GOTO);
    EXPECT_EQ(keywordsMap.at("if"), TokenType::IF);
    EXPECT_EQ(keywordsMap.at("inline"), TokenType::INLINE);
    EXPECT_EQ(keywordsMap.at("int"), TokenType::INT);
    EXPECT_EQ(keywordsMap.at("long"), TokenType::LONG);
    EXPECT_EQ(keywordsMap.at("mutable"), TokenType::MUTABLE);
    EXPECT_EQ(keywordsMap.at("namespace"), TokenType::NAMESPACE);
    EXPECT_EQ(keywordsMap.at("new"), TokenType::NEW);
    EXPECT_EQ(keywordsMap.at("noexcept"), TokenType::NOEXCEPT);
    EXPECT_EQ(keywordsMap.at("nullptr"), TokenType::NULLPTR);
    EXPECT_EQ(keywordsMap.at("operator"), TokenType::OPERATOR);
    EXPECT_EQ(keywordsMap.at("or"), TokenType::OR);
    EXPECT_EQ(keywordsMap.at("or_eq"), TokenType::OR_EQ);
    EXPECT_EQ(keywordsMap.at("private"), TokenType::PRIVATE);
    EXPECT_EQ(keywordsMap.at("protected"), TokenType::PROTECTED);
    EXPECT_EQ(keywordsMap.at("public"), TokenType::PUBLIC);
    EXPECT_EQ(keywordsMap.at("register"), TokenType::REGISTER);
    EXPECT_EQ(keywordsMap.at("reinterpret_cast"), TokenType::REINTERPRET_CAST);
    EXPECT_EQ(keywordsMap.at("requires"), TokenType::REQUIRES);
    EXPECT_EQ(keywordsMap.at("return"), TokenType::RETURN);
    EXPECT_EQ(keywordsMap.at("short"), TokenType::SHORT);
    EXPECT_EQ(keywordsMap.at("signed"), TokenType::SIGNED);
    EXPECT_EQ(keywordsMap.at("sizeof"), TokenType::SIZEOF);
    EXPECT_EQ(keywordsMap.at("static"), TokenType::STATIC);
    EXPECT_EQ(keywordsMap.at("static_assert"), TokenType::STATIC_ASSERT);
    EXPECT_EQ(keywordsMap.at("static_cast"), TokenType::STATIC_CAST);
    EXPECT_EQ(keywordsMap.at("struct"), TokenType::STRUCT);
    EXPECT_EQ(keywordsMap.at("switch"), TokenType::SWITCH);
    EXPECT_EQ(keywordsMap.at("template"), TokenType::TEMPLATE);
    EXPECT_EQ(keywordsMap.at("this"), TokenType::THIS);
    EXPECT_EQ(keywordsMap.at("thread_local"), TokenType::THREAD_LOCAL);
    EXPECT_EQ(keywordsMap.at("throw"), TokenType::THROW);
    EXPECT_EQ(keywordsMap.at("true"), TokenType::TRUE);
    EXPECT_EQ(keywordsMap.at("try"), TokenType::TRY);
    EXPECT_EQ(keywordsMap.at("typedef"), TokenType::TYPEDEF);
    EXPECT_EQ(keywordsMap.at("typeid"), TokenType::TYPEID);
    EXPECT_EQ(keywordsMap.at("typename"), TokenType::TYPENAME);
    EXPECT_EQ(keywordsMap.at("union"), TokenType::UNION);
    EXPECT_EQ(keywordsMap.at("unsigned"), TokenType::UNSIGNED);
    EXPECT_EQ(keywordsMap.at("using"), TokenType::USING);
    EXPECT_EQ(keywordsMap.at("virtual"), TokenType::VIRTUAL);
    EXPECT_EQ(keywordsMap.at("void"), TokenType::VOID);
    EXPECT_EQ(keywordsMap.at("volatile"), TokenType::VOLATILE);
    EXPECT_EQ(keywordsMap.at("wchar_t"), TokenType::WCHAR_T);
    EXPECT_EQ(keywordsMap.at("while"), TokenType::WHILE);
    EXPECT_EQ(keywordsMap.at("xor"), TokenType::XOR);
    EXPECT_EQ(keywordsMap.at("xor_eq"), TokenType::XOR_EQ);

    // Check that the map size matches the number of unique keywords
    std::set<std::string> unique_keywords;
    for (const auto& kv : keywordsMap)
    {
        unique_keywords.insert(kv.first);
    }
    EXPECT_EQ(keywordsMap.size(), unique_keywords.size());

    // Check that a non-existent keyword is not present
    EXPECT_EQ(keywordsMap.count("nonexistent"), 0);
}
