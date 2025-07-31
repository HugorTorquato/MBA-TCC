#include "PrettyPrintVisitor.h"

#include "../../Logger/Log.h"
#include "Expressions.h"

namespace
{
bool returnEmptystringIfInvalid(Expression* expr)
{
    if (!expr || expr == nullptr)
    {
        Logger::getInstance().log(
            "[PrettyPrintVisitor][returnEmptystringIfInvalid] Expression is "
            "null, returning empty string.");
        return true;
    }
    return false;
}
}  // namespace

std::string PrettyPrintVisitor::visitBinaryExpression(BinaryExpression* expr)
{
    Logger::getInstance().log(
        "[PrettyPrintVisitor][visitBinaryExpression] Visiting binary expression.");
    if (returnEmptystringIfInvalid(expr)) return "";

    return expr->getLeft()->accept(this) + " " + expr->getOperator() + " " +
           expr->getRight()->accept(this);
}
std::string PrettyPrintVisitor::visitGroupingExpression(GroupingExpression* expr)
{
    Logger::getInstance().log(
        "[PrettyPrintVisitor][visitGroupingExpression] Visiting grouping expression.");
    if (returnEmptystringIfInvalid(expr)) return "";

    return "(" + expr->getExpression()->accept(this) + ")";
}
std::string PrettyPrintVisitor::visitLiteralExpression(LiteralExpression* expr)
{
    Logger::getInstance().log(
        "[PrettyPrintVisitor][visitLiteralExpression] Visiting literal expression.");
    if (returnEmptystringIfInvalid(expr)) return "";

    return expr->getValue();  // Assuming value is a string representation
}
std::string PrettyPrintVisitor::visitUnaryExpression(UnaryExpression* expr)
{
    Logger::getInstance().log(
        "[PrettyPrintVisitor][visitUnaryExpression] Visiting unary expression.");
    if (returnEmptystringIfInvalid(expr)) return "";

    return expr->getOperator() + expr->getRight()->accept(this);
}
