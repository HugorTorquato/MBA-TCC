#include "../../../src/ProcessSourceFiles/SyntaxTrees/PrettyPrintVisitor.h"

#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/SyntaxTrees/Expressions.h"

class PrettyPrintVisitorTests : public ::testing::Test
{
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(PrettyPrintVisitorTests, VisitBinaryExpression)
{
    Expression* left = new LiteralExpression("left");
    Expression* right = new LiteralExpression("right");
    BinaryExpression expr(left, right, "+");
    GroupingExpression groupExpr(new BinaryExpression(expr));

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupExpr.accept(&visitor), "(left + right)");

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
    UnaryExpression expr("-", right);
    GroupingExpression groupExpr(new UnaryExpression(expr));

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupExpr.accept(&visitor), "(-right)");

    delete right;
}

TEST_F(PrettyPrintVisitorTests, VisitMultipleExpressions)
{
    Expression* left = new LiteralExpression("left");
    Expression* right = new LiteralExpression("right");
    BinaryExpression binaryExpr(left, right, "+");
    GroupingExpression groupbinaryExpr(new BinaryExpression(binaryExpr));

    GroupingExpression groupingExpr(new LiteralExpression("grouped"));

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupbinaryExpr.accept(&visitor), "(left + right)");
    EXPECT_EQ(groupingExpr.accept(&visitor), "(grouped)");

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
    LiteralExpression expr("123");
    PrettyPrintVisitor visitor;

    std::string result = expr.accept(&visitor);

    EXPECT_EQ(result, "123");
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
    delete unary;
    delete group;
}