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
    std::shared_ptr<Expression> left = std::make_shared<LiteralExpression>("left");
    std::shared_ptr<Expression> right = std::make_shared<LiteralExpression>("right");
    std::shared_ptr<Expression> expr = std::make_shared<BinaryExpression>(left, right, "+");
    std::shared_ptr<Expression> groupExpr = std::make_shared<GroupingExpression>(expr);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupExpr->accept(&visitor), "(left + right)");
}

TEST_F(PrettyPrintVisitorTests, VisitGroupingExpression)
{
    std::shared_ptr<Expression> inner = std::make_shared<LiteralExpression>("inner");
    GroupingExpression expr(inner);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(expr.accept(&visitor), "(inner)");
}

TEST_F(PrettyPrintVisitorTests, VisitLiteralExpression)
{
    LiteralExpression expr("literal");

    PrettyPrintVisitor visitor;
    EXPECT_EQ(expr.accept(&visitor), "literal");
}

TEST_F(PrettyPrintVisitorTests, VisitUnaryExpression)
{
    std::shared_ptr<Expression> right = std::make_shared<LiteralExpression>("right");
    std::shared_ptr<Expression> expr = std::make_shared<UnaryExpression>("-", right);
    std::shared_ptr<Expression> groupExpr = std::make_shared<GroupingExpression>(expr);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupExpr->accept(&visitor), "(-right)");
}

TEST_F(PrettyPrintVisitorTests, VisitMultipleExpressions)
{
    std::shared_ptr<Expression> left = std::make_shared<LiteralExpression>("left");
    std::shared_ptr<Expression> right = std::make_shared<LiteralExpression>("right");
    std::shared_ptr<Expression> binaryExpr = std::make_shared<BinaryExpression>(left, right, "+");
    std::shared_ptr<Expression> groupbinaryExpr = std::make_shared<GroupingExpression>(binaryExpr);

    std::shared_ptr<Expression> grouped = std::make_shared<LiteralExpression>("grouped");
    std::shared_ptr<Expression> groupingExpr = std::make_shared<GroupingExpression>(grouped);

    PrettyPrintVisitor visitor;
    EXPECT_EQ(groupbinaryExpr->accept(&visitor), "(left + right)");
    EXPECT_EQ(groupingExpr->accept(&visitor), "(grouped)");
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
    std::shared_ptr<Expression> expr = std::make_shared<LiteralExpression>("123");
    PrettyPrintVisitor visitor;

    std::string result = expr->accept(&visitor);

    EXPECT_EQ(result, "123");
}

TEST_F(PrettyPrintVisitorTests, UnaryExpression)
{
    std::shared_ptr<LiteralExpression> lit = std::make_shared<LiteralExpression>("true");
    UnaryExpression expr("!", lit);
    PrettyPrintVisitor visitor;

    std::string result = expr.accept(&visitor);

    EXPECT_EQ(result, "!true");
}

TEST_F(PrettyPrintVisitorTests, NestedExpressions)
{
    // Represents: (!(1 + 2))
    std::shared_ptr<Expression> left = std::make_shared<LiteralExpression>("1");
    std::shared_ptr<Expression> right = std::make_shared<LiteralExpression>("2");
    std::shared_ptr<Expression> bin = std::make_shared<BinaryExpression>(left, right, "+");
    std::shared_ptr<Expression> groupBin = std::make_shared<GroupingExpression>(bin);
    std::shared_ptr<Expression> unary = std::make_shared<UnaryExpression>("!", groupBin);
    std::shared_ptr<Expression> group = std::make_shared<GroupingExpression>(unary);

    PrettyPrintVisitor visitor;
    std::string result = group->accept(&visitor);

    EXPECT_EQ(result, "(!(1 + 2))");
}
