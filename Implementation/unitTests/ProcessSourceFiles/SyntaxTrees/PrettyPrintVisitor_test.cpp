#include "../../../src/ProcessSourceFiles/SyntaxTrees/PrettyPrintVisitor.h"

#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/SyntaxTrees/Expressions.h"

class PrettyPrintVisitorTests : public ::testing::Test
{
    void SetUp() override {}

    void TearDown() override {}
};

//TODO:Implement tests with smart pointers

TEST_F(PrettyPrintVisitorTests, VisitBinaryExpression)
{
    Expression* left = new LiteralExpression("left");
    Expression* right = new LiteralExpression("right");
    Expression* expr = new BinaryExpression(left, right, "+");
    Expression* groupExpr = new GroupingExpression(expr);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupExpr->accept(&visitor), "(left + right)");

    delete groupExpr;
    delete expr;
    delete left;
    delete right;
    
}

TEST_F(PrettyPrintVisitorTests, VisitGroupingExpression)
{
    Expression* inner = new LiteralExpression("inner");
    GroupingExpression expr(inner);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(expr.accept(&visitor), "(inner)");

    delete inner;
}

TEST_F(PrettyPrintVisitorTests, VisitLiteralExpression)
{
    LiteralExpression expr("literal");

    PrettyPrintVisitor visitor;
    EXPECT_EQ(expr.accept(&visitor), "literal");
}

TEST_F(PrettyPrintVisitorTests, VisitUnaryExpression)
{
    Expression* right = new LiteralExpression("right");
    Expression* expr = new UnaryExpression("-", right);
    Expression* groupExpr = new GroupingExpression(expr);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupExpr->accept(&visitor), "(-right)");

    delete groupExpr;
    delete expr;
    delete right;
}

TEST_F(PrettyPrintVisitorTests, VisitMultipleExpressions)
{
    Expression* left = new LiteralExpression("left");
    Expression* right = new LiteralExpression("right");
    Expression* binaryExpr = new BinaryExpression(left, right, "+");
    Expression* groupbinaryExpr = new GroupingExpression(binaryExpr);

    Expression* grouped = new LiteralExpression("grouped");
    Expression* groupingExpr = new GroupingExpression(grouped);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupbinaryExpr->accept(&visitor), "(left + right)");
    EXPECT_EQ(groupingExpr->accept(&visitor), "(grouped)");

    delete groupingExpr;
    delete grouped;
    delete groupbinaryExpr;
    delete binaryExpr;
    delete left;
    delete right;
}
TEST_F(PrettyPrintVisitorTests, VisitEmptyExpressions)
{
    PrettyPrintVisitor visitor;
    EXPECT_EQ(visitor.visitBinaryExpression(nullptr), "");
    EXPECT_EQ(visitor.visitGroupingExpression(nullptr), "");
    EXPECT_EQ(visitor.visitLiteralExpression(nullptr), "");
    EXPECT_EQ(visitor.visitUnaryExpression(nullptr), "");
}
TEST_F(PrettyPrintVisitorTests, LiteralOnly)
{
    Expression* expr = new LiteralExpression("123");
    PrettyPrintVisitor visitor;

    std::string result = expr->accept(&visitor);

    EXPECT_EQ(result, "123");

    delete expr;
}

TEST_F(PrettyPrintVisitorTests, UnaryExpression)
{
    LiteralExpression* lit = new LiteralExpression("true");
    UnaryExpression expr("!", lit);
    PrettyPrintVisitor visitor;

    std::string result = expr.accept(&visitor);

    EXPECT_EQ(result, "!true");

    delete lit;
}

TEST_F(PrettyPrintVisitorTests, NestedExpressions)
{
    // Represents: (!(1 + 2))
    Expression* left = new LiteralExpression("1");
    Expression* right = new LiteralExpression("2");
    Expression* bin = new BinaryExpression(left, right, "+");
    Expression* groupBin = new GroupingExpression(bin);
    Expression* unary = new UnaryExpression("!", groupBin);
    Expression* group = new GroupingExpression(unary);

    PrettyPrintVisitor visitor;
    std::string result = group->accept(&visitor);

    EXPECT_EQ(result, "(!(1 + 2))");

    delete left;
    delete right;
    delete bin;
    delete groupBin;
    delete unary;
    delete group;
}