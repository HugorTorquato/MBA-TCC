#include "../../../src/ProcessSourceFiles/Scanner/Token.h"

#include <gtest/gtest.h>

class TokenTest : public ::testing::Test
{
   protected:
    LineFile DefaultLineFile{1, 2, 3, 4};

    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(TokenTest, DefaultConstructor)
{
    Token token;
    EXPECT_EQ(token.toString(),
              "Token Type: UNKNOWN, Lexeme: , LineFile: [LineFile] Line: 0, Col: 0, End Line: 0, "
              "End Col: 0");
}

TEST_F(TokenTest, ParameterizedConstructor)
{
    Token token(TokenType::IDENTIFIER, "myVariable", DefaultLineFile);
    EXPECT_EQ(token.toString(),
              "Token Type: IDENTIFIER, Lexeme: myVariable, LineFile: [LineFile] Line: 1, Col: 2, "
              "End Line: 3, End Col: 4");
}

TEST_F(TokenTest, ToStringWithEmptyLexemeReturnsUnknownType)
{
    Token token(TokenType::IDENTIFIER, "", DefaultLineFile);
    EXPECT_EQ(token.toString(),
              "Token Type: UNKNOWN, Lexeme: , LineFile: [LineFile] Line: 1, Col: 2, End Line: 3, "
              "End Col: 4");
}

TEST_F(TokenTest, ToStringWithDifferentLineFile)
{
    LineFile lineFile(5, 6, 7, 8);
    Token token(TokenType::NUMBER, "42", lineFile);
    EXPECT_EQ(token.toString(),
              "Token Type: NUMBER, Lexeme: 42, LineFile: [LineFile] Line: 5, Col: 6, End Line: 7, "
              "End Col: 8");
}

TEST_F(TokenTest, GetTypeReturnsCorrectType)
{
    Token token(TokenType::STRING, "Hello, World!", DefaultLineFile);
    EXPECT_EQ(token.getType(), "STRING");
}

TEST_F(TokenTest, GetLexemeReturnsCorrectLexeme)
{
    Token token(TokenType::NUMBER, "12345", DefaultLineFile);
    EXPECT_EQ(token.getLexeme(), "12345");
}

TEST_F(TokenTest, GetLineFileReturnsCorrectLineFile)
{
    Token token(TokenType::IDENTIFIER, "myVar", DefaultLineFile);
    EXPECT_EQ(token.getLineFile(), "[LineFile] Line: 1, Col: 2, End Line: 3, End Col: 4");
}
