#include "../../../src/ProcessSourceFiles/Parser/Parser.h"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

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

TEST_F(ParserTest, SimpleExpressionExemple)
{
    // 1 + 2 * 3
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 3, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::STAR, "*", LineFile(1, 4, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "3", LineFile(1, 5, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.expression();

    ASSERT_NE(expr, nullptr);
    EXPECT_EQ(expr->getType(), "BINARY_EXPRESSION");
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
    ASSERT_NE(binaryExpr, nullptr);
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "1");
    EXPECT_EQ(binaryExpr->getOperator(), "+");
    auto rightExpr = std::dynamic_pointer_cast<BinaryExpression>(binaryExpr->getRight());
    ASSERT_NE(rightExpr, nullptr);
    left = std::dynamic_pointer_cast<LiteralExpression>(rightExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "2");
    EXPECT_EQ(rightExpr->getOperator(), "*");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(rightExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "3");
}

TEST_F(ParserTest, ConsumeTokenType)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "123", LineFile(1, 1, 0, 0)));

    Parser parser(tokens);
    auto token = parser.parse();

    ASSERT_NE(token, nullptr);
    auto literalExpr = std::dynamic_pointer_cast<LiteralExpression>(token);
    ASSERT_NE(literalExpr, nullptr);
    EXPECT_EQ(literalExpr->getValue(), "123");
    EXPECT_EQ(literalExpr->getType(), "LITERAL_EXPRESSION");
    // EXPECT_EQ(token->getValue(), "int");
}

// INT is not suporter to parse yet.. just expressions

TEST_F(ParserTest, SixLayersExpression)
{
    // 10 - 2 + 2 + 2 + 2 + 2
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "10", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::MINUS, "-", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 3, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 4, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 5, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 6, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 8, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 9, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 8, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 9, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    ASSERT_NE(expr, nullptr);

    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
    ASSERT_NE(binaryExpr, nullptr);
    EXPECT_EQ(binaryExpr->getLeft()->getType(), "LITERAL_EXPRESSION");
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "10");
    EXPECT_EQ(binaryExpr->getOperator(), "-");
    EXPECT_EQ(binaryExpr->getRight()->getType(), "BINARY_EXPRESSION");
    auto rightExpr = std::dynamic_pointer_cast<BinaryExpression>(binaryExpr->getRight());
    ASSERT_NE(rightExpr, nullptr);
    EXPECT_EQ(rightExpr->getLeft()->getType(), "LITERAL_EXPRESSION");
    left = std::dynamic_pointer_cast<LiteralExpression>(rightExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "2");
    EXPECT_EQ(rightExpr->getOperator(), "+");
    EXPECT_EQ(rightExpr->getRight()->getType(), "BINARY_EXPRESSION");
    rightExpr = std::dynamic_pointer_cast<BinaryExpression>(rightExpr->getRight());
    ASSERT_NE(rightExpr, nullptr);
    EXPECT_EQ(rightExpr->getLeft()->getType(), "LITERAL_EXPRESSION");
    left = std::dynamic_pointer_cast<LiteralExpression>(rightExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "2");
    EXPECT_EQ(rightExpr->getOperator(), "+");
    EXPECT_EQ(rightExpr->getRight()->getType(), "BINARY_EXPRESSION");
    rightExpr = std::dynamic_pointer_cast<BinaryExpression>(rightExpr->getRight());
    ASSERT_NE(rightExpr, nullptr);
    EXPECT_EQ(rightExpr->getLeft()->getType(), "LITERAL_EXPRESSION");
    left = std::dynamic_pointer_cast<LiteralExpression>(rightExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "2");
    EXPECT_EQ(rightExpr->getOperator(), "+");
    EXPECT_EQ(rightExpr->getRight()->getType(), "BINARY_EXPRESSION");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(rightExpr->getLeft());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getType(), "LITERAL_EXPRESSION");
    auto rightLeft = std::dynamic_pointer_cast<LiteralExpression>(right);
    ASSERT_NE(rightLeft, nullptr);
    EXPECT_EQ(rightLeft->getValue(), "2");
    left = std::dynamic_pointer_cast<LiteralExpression>(rightExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "2");
}

TEST_F(ParserTest, Expression_Equality)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::IDENTIFIER, "x", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::EQUAL_EQUAL, "==", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "42", LineFile(1, 4, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
    EXPECT_EQ(binaryExpr->getLeft()->getType(), "LITERAL_EXPRESSION");
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    EXPECT_EQ(left->getValue(), "x");
    EXPECT_EQ(binaryExpr->getOperator(), "==");
    EXPECT_EQ(binaryExpr->getRight()->getType(), "LITERAL_EXPRESSION");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    EXPECT_EQ(right->getValue(), "42");
}

TEST_F(ParserTest, Expression_Grouping)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_PAREN, "(", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 3, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 4, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_PAREN, ")", LineFile(1, 5, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto groupingExpr = std::dynamic_pointer_cast<GroupingExpression>(expr);
    ASSERT_NE(groupingExpr, nullptr);
    EXPECT_EQ(groupingExpr->getExpression()->getType(), "BINARY_EXPRESSION");
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(groupingExpr->getExpression());
    ASSERT_NE(binaryExpr, nullptr);
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "1");
    EXPECT_EQ(binaryExpr->getOperator(), "+");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "2");
}

TEST_F(ParserTest, Expression_Unary)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::MINUS, "-", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "5", LineFile(1, 2, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto unaryExpr = std::dynamic_pointer_cast<UnaryExpression>(expr);
    ASSERT_NE(unaryExpr, nullptr);
    EXPECT_EQ(unaryExpr->getOperator(), "-");
    EXPECT_EQ(unaryExpr->getRight()->getType(), "LITERAL_EXPRESSION");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(unaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "5");
}

TEST_F(ParserTest, Expression_Binary)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "3", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "4", LineFile(1, 3, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
    ASSERT_NE(binaryExpr, nullptr);
    EXPECT_EQ(binaryExpr->getLeft()->getType(), "LITERAL_EXPRESSION");
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "3");
    EXPECT_EQ(binaryExpr->getOperator(), "+");
    EXPECT_EQ(binaryExpr->getRight()->getType(), "LITERAL_EXPRESSION");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "4");
}

TEST_F(ParserTest, Expression_Complex)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_PAREN, "(", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 3, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 4, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_PAREN, ")", LineFile(1, 5, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::STAR, "*", LineFile(1, 6, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "3", LineFile(1, 7, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
    ASSERT_NE(binaryExpr, nullptr);
    EXPECT_EQ(binaryExpr->getLeft()->getType(), "GROUPING_EXPRESSION");
    auto groupingExpr = std::dynamic_pointer_cast<GroupingExpression>(binaryExpr->getLeft());
    ASSERT_NE(groupingExpr, nullptr);
    EXPECT_EQ(groupingExpr->getExpression()->getType(), "BINARY_EXPRESSION");
    auto innerBinaryExpr =
        std::dynamic_pointer_cast<BinaryExpression>(groupingExpr->getExpression());
    ASSERT_NE(innerBinaryExpr, nullptr);
    auto left = std::dynamic_pointer_cast<LiteralExpression>(innerBinaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "1");
    EXPECT_EQ(innerBinaryExpr->getOperator(), "+");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(innerBinaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "2");
    EXPECT_EQ(binaryExpr->getOperator(), "*");
    EXPECT_EQ(binaryExpr->getRight()->getType(), "LITERAL_EXPRESSION");
    right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "3");
}

TEST_F(ParserTest, Expression_Empty)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    Parser parser(tokens);
    auto expr = parser.parse();
    EXPECT_EQ(expr, nullptr);
}

TEST_F(ParserTest, Expression_Error_EndOfFileToken)
{
    auto eofToken = std::make_shared<Token>(TokenType::END_OF_FILE, "", LineFile(1, 1, 0, 0));
    Parser parser({eofToken});
    auto expr = parser.parse();
    EXPECT_EQ(expr, nullptr);
}

TEST_F(ParserTest, Expression_Error_NonEofToken)
{
    auto numToken = std::make_shared<Token>(TokenType::NUMBER, "42", LineFile(1, 1, 0, 0));
    Parser parser({numToken});
    auto expr = parser.parse();
    EXPECT_NE(expr, nullptr);
    auto literalExpr = std::dynamic_pointer_cast<LiteralExpression>(expr);
    ASSERT_NE(literalExpr, nullptr);
    EXPECT_EQ(literalExpr->getValue(), "42");
    EXPECT_EQ(literalExpr->getType(), "LITERAL_EXPRESSION");
}

TEST_F(ParserTest, Expression_Invalid)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 2, 0, 0)));
    // Missing right operand
    Parser parser(tokens);
    EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST_F(ParserTest, Expression_ComplexWithUnary)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::MINUS, "-", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_PAREN, "(", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "5", LineFile(1, 3, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PLUS, "+", LineFile(1, 4, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "3", LineFile(1, 5, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_PAREN, ")", LineFile(1, 6, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto unaryExpr = std::dynamic_pointer_cast<UnaryExpression>(expr);
    ASSERT_NE(unaryExpr, nullptr);
    EXPECT_EQ(unaryExpr->getOperator(), "-");
    EXPECT_EQ(unaryExpr->getRight()->getType(), "GROUPING_EXPRESSION");
    auto groupingExpr = std::dynamic_pointer_cast<GroupingExpression>(unaryExpr->getRight());
    ASSERT_NE(groupingExpr, nullptr);
    EXPECT_EQ(groupingExpr->getExpression()->getType(), "BINARY_EXPRESSION");
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(groupingExpr->getExpression());
    ASSERT_NE(binaryExpr, nullptr);
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "5");
    EXPECT_EQ(binaryExpr->getOperator(), "+");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "3");
}

TEST_F(ParserTest, Expression_Equality_WithNumbers)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::EQUAL_EQUAL, "==", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 3, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
    ASSERT_NE(binaryExpr, nullptr);
    EXPECT_EQ(binaryExpr->getOperator(), "==");
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "1");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "2");
}

TEST_F(ParserTest, Expression_Inequality_WithNumbers)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::BANG_EQUAL, "!=", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 3, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr);
    ASSERT_NE(binaryExpr, nullptr);
    EXPECT_EQ(binaryExpr->getOperator(), "!=");
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "1");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "2");
}

// Right Param

TEST_F(ParserTest, Expression_RightParam_simple)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_PAREN, "(", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_PAREN, ")", LineFile(1, 3, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto groupingExpr = std::dynamic_pointer_cast<GroupingExpression>(expr);
    ASSERT_NE(groupingExpr, nullptr);
    EXPECT_EQ(groupingExpr->getExpression()->getType(), "LITERAL_EXPRESSION");
    auto literalExpr = std::dynamic_pointer_cast<LiteralExpression>(groupingExpr->getExpression());
    ASSERT_NE(literalExpr, nullptr);
    EXPECT_EQ(literalExpr->getValue(), "1");
}

TEST_F(ParserTest, Expression_RightParam)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_PAREN, "(", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "1", LineFile(1, 2, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::BANG_EQUAL, "!=", LineFile(1, 4, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::NUMBER, "2", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_PAREN, ")", LineFile(1, 8, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();

    EXPECT_NE(expr, nullptr);
    auto groupingExpr = std::dynamic_pointer_cast<GroupingExpression>(expr);
    ASSERT_NE(groupingExpr, nullptr);
    EXPECT_EQ(groupingExpr->getType(), "GROUPING_EXPRESSION");
    EXPECT_NE(groupingExpr->getExpression(), nullptr);
    auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(groupingExpr->getExpression());
    ASSERT_NE(binaryExpr, nullptr);
    EXPECT_EQ(binaryExpr->getOperator(), "!=");
    auto left = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getLeft());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->getValue(), "1");
    auto right = std::dynamic_pointer_cast<LiteralExpression>(binaryExpr->getRight());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getValue(), "2");
}

TEST_F(ParserTest, Class_SimpleDeclaration_Missing_IDENTIFIER)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::CLASS, "class", LineFile(1, 1, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_BRACE, "{", LineFile(1, 15, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_BRACE, "}", LineFile(1, 16, 0, 0)));

    Parser parser(tokens);
    EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST_F(ParserTest, Class_SimpleDeclarationWthParentClass_Missing_Access_Type)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::CLASS, "class", LineFile(1, 1, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyClass", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::COLON, ":", LineFile(1, 15, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyParentClass", LineFile(1, 25, 0, 0)));

    Parser parser(tokens);
    EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST_F(ParserTest, Class_SimpleDeclarationWthParentClass_Missing_ParentClss_IDENTIFIER)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::CLASS, "class", LineFile(1, 1, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyClass", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::COLON, ":", LineFile(1, 15, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PUBLIC, "public", LineFile(1, 22, 0, 0)));

    Parser parser(tokens);
    EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST_F(ParserTest, Class_SimpleDeclaration_Missing_RightBrace)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::CLASS, "class", LineFile(1, 1, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyClass", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_BRACE, "{", LineFile(1, 15, 0, 0)));

    Parser parser(tokens);
    EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST_F(ParserTest, Class_SimpleDeclaration)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::CLASS, "class", LineFile(1, 1, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyClass", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::LEFT_BRACE, "{", LineFile(1, 15, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::RIGHT_BRACE, "}", LineFile(1, 16, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();
}

TEST_F(ParserTest, Class_SimpleDeclarationWthParentClass)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::CLASS, "class", LineFile(1, 1, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyClass", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::COLON, ":", LineFile(1, 15, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PUBLIC, "public", LineFile(1, 22, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyParentClass", LineFile(1, 25, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();
}

TEST_F(ParserTest, Class_SimpleDeclarationWthMultipleParentClass)
{
    std::vector<std::shared_ptr<IToken>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::CLASS, "class", LineFile(1, 1, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyClass", LineFile(1, 7, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::COLON, ":", LineFile(1, 15, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PUBLIC, "public", LineFile(1, 22, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyParentClass", LineFile(1, 25, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::COMMA, ",", LineFile(1, 39, 0, 0)));
    tokens.push_back(std::make_shared<Token>(TokenType::PUBLIC, "public", LineFile(1, 22, 0, 0)));
    tokens.push_back(
        std::make_shared<Token>(TokenType::IDENTIFIER, "MyParentClass2", LineFile(1, 25, 0, 0)));

    Parser parser(tokens);
    auto expr = parser.parse();
}