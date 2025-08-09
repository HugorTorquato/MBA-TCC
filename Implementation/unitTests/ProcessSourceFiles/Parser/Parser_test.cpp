#include "../../../src/ProcessSourceFiles/Parser/Parser.h"

#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"
#include "../../../src/ProcessSourceFiles/SyntaxTrees/Expressions.h"

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

TEST_F(ParserTest, PeekTokenFromVector)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::INT, "int", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::IDENTIFIER, "myVar", LineFile(1, 4, 0, 0)));
    Parser parser(tokens);

    auto result = parser.ListIncomingTokens();
    ASSERT_EQ(result.size(), 2);

    auto tokenAtIndex0 = parser.peekIndex(0);
    ASSERT_NE(tokenAtIndex0, nullptr);
    EXPECT_EQ(tokenAtIndex0->getType(), "INT");
    EXPECT_EQ(tokenAtIndex0->getLexeme(), "int");

    auto tokenAtIndex1 = parser.peekIndex(1);
    ASSERT_NE(tokenAtIndex1, nullptr);
    EXPECT_EQ(tokenAtIndex1->getType(), "IDENTIFIER");
    EXPECT_EQ(tokenAtIndex1->getLexeme(), "myVar");
}

TEST_F(ParserTest, PeekCurrentToken)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::INT, "int", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::IDENTIFIER, "myVar", LineFile(1, 4, 0, 0)));
    Parser parser(tokens);

    auto currentToken = parser.peekIndex(0);
    ASSERT_NE(currentToken, nullptr);
    EXPECT_EQ(currentToken->getType(), "INT");
    EXPECT_EQ(currentToken->getLexeme(), "int");

    currentToken = parser.peekIndex(1);
    ASSERT_NE(currentToken, nullptr);
    EXPECT_EQ(currentToken->getType(), "IDENTIFIER");
    EXPECT_EQ(currentToken->getLexeme(), "myVar");
}

// TEST_F(ParserTest, SimpleExpressionExemple)
// {
//     // 1 + 2 * 3
//     std::vector<std::shared_ptr<IToken>> tokens;
//     tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 1, 0, 0)));
//     tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 2, 0, 0)));
//     tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 3, 0, 0)));
//     tokens.push_back(std::make_shared<Token>(TokenType::STAR, "*", LineFile(1, 4, 0, 0)));
//     tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "3", LineFile(1, 5, 0, 0)));

//     Parser parser(tokens);
//     auto expr = parser.expression();

//     ASSERT_NE(expr, nullptr);
//     EXPECT_EQ(expr->getType(), "BINARY_EXPRESSION");
//     auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
//     ASSERT_NE(binaryExpr, nullptr);
//     // EXPECT_EQ(binaryExpr->getLeft()->getLexeme(), "1");
//     EXPECT_EQ(binaryExpr->getOperator(), "+");
//     auto rightExpr = std::dynamic_pointer_cast<BinaryExpression>(binaryExpr->getRight());
//     ASSERT_NE(rightExpr, nullptr);
//     // EXPECT_EQ(rightExpr->getLeft()->getLexeme(), "2");
//     EXPECT_EQ(rightExpr->getOperator(), "*");
//     // EXPECT_EQ(rightExpr->getRight()->getLexeme(), "3");
// }

// TEST_F(ParserTest, Expression_Equality)
// {
//     std::vector<std::shared_ptr<IToken>> tokens;
//     tokens.push_back(std::make_shared<Token>(TokenType::IDENTIFIER, "x", LineFile(1, 1, 0, 0)));
//     tokens.push_back(std::make_shared<Token>(TokenType::EQUAL_EQUAL, "==", LineFile(1, 2, 0,
//     0))); tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "42", LineFile(1, 4, 0,
//     0)));

//     Parser parser(tokens);
//     auto expr = parser.expression();

//     EXPECT_EQ(expr->getType(), "BINARY_EXPRESSION");
//     EXPECT_EQ(expr->getLeft()->getLexeme(), "x");
//     EXPECT_EQ(expr->getRight()->getLexeme(), "42");
// }