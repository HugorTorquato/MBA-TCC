#include "PrettyPrintVisitor.h"

#include "Expressions.h"

std::string PrettyPrintVisitor::visitBinaryExpression(BinaryExpression* expr)
{
    return expr->getLeft()->accept(this) + " " + expr->getOperator() + " " +
           expr->getRight()->accept(this);
}
std::string PrettyPrintVisitor::visitGroupingExpression(GroupingExpression* expr)
{
    return "(" + expr->getExpression()->accept(this) + ")";
}
std::string PrettyPrintVisitor::visitLiteralExpression(LiteralExpression* expr)
{
    return expr->getValue();  // Assuming value is a string representation
}
std::string PrettyPrintVisitor::visitUnaryExpression(UnaryExpression* expr)
{
    return expr->getOperator() + expr->getRight()->accept(this);
}
