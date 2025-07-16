#include "../../../src/ProcessSourceFiles/Scanner/TokenType.h"

#include <gtest/gtest.h>

class TokenTypeTest : public ::testing::Test
{
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(TokenTypeTest, ToString_ReturnsCorrectString)
{
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::LEFT_PAREN), "LEFT_PAREN");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::RIGHT_PAREN), "RIGHT_PAREN");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::LEFT_BRACE), "LEFT_BRACE");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::RIGHT_BRACE), "RIGHT_BRACE");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::COMMA), "COMMA");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::DOT), "DOT");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::MINUS), "MINUS");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::PLUS), "PLUS");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::SEMICOLON), "SEMICOLON");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::SLASH), "SLASH");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::STAR), "STAR");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::BANG), "BANG");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::BANG_EQUAL), "BANG_EQUAL");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::EQUAL), "EQUAL");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::EQUAL_EQUAL), "EQUAL_EQUAL");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::GREATER), "GREATER");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::GREATER_EQUAL), "GREATER_EQUAL");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::LESS), "LESS");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::LESS_EQUAL), "LESS_EQUAL");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::IDENTIFIER), "IDENTIFIER");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::STRING), "STRING");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::NUMBER), "NUMBER");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::AND), "AND");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::CLASS), "CLASS");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::ELSE), "ELSE");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::FALSE), "FALSE");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::FUN), "FUN");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::FOR), "FOR");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::IF), "IF");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::NIL), "NIL");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::OR), "OR");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::PRINT), "PRINT");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::RETURN), "RETURN");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::SUPER), "SUPER");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::THIS), "THIS");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::TRUE), "TRUE");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::VAR), "VAR");
    EXPECT_EQ(TokenTypeNameSpace::toString(TokenType::WHILE), "WHILE");
}
