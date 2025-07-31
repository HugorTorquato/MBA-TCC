#include "../../../src/ProcessSourceFiles/Parser/Parser.h"

#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"

class ParserTest : public ::testing::Test
{
   protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ParserTest, ListIncomingTokens_Empty)
{
    Parser parser({});
    auto tokens = parser.ListIncomingTokens();
    EXPECT_TRUE(tokens.empty());
}

TEST_F(ParserTest, ListIncomingTokens_SingleToken)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::INT, "int", LineFile(1, 1, 0, 0)));
    Parser parser(tokens);

    auto result = parser.ListIncomingTokens();
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0],
              "Token Type: INT, Lexeme: int, LineFile: [LineFile] Line: 1, Col: 1, End Line: 0, "
              "End Col: 0");
}

TEST_F(ParserTest, ListIncomingTokens_MultipleTokens)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::INT, "int", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::IDENTIFIER, "myVar", LineFile(1, 4, 0, 0)));
    Parser parser(tokens);

    auto result = parser.ListIncomingTokens();
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0],
              "Token Type: INT, Lexeme: int, LineFile: [LineFile] Line: 1, Col: 1, End Line: 0, "
              "End Col: 0");
    EXPECT_EQ(result[1],
              "Token Type: IDENTIFIER, Lexeme: myVar, LineFile: [LineFile] Line: 1, Col: 4, End "
              "Line: 0, End Col: 0");
}
