#include "Expressions.h"

BinaryExpression::BinaryExpression(Expression* left, Expression* right, const std::string& op)
    : left(left), right(right), op(op)
{
}

Expression* BinaryExpression::getLeft() const
{
    return left;
}

Expression* BinaryExpression::getRight() const
{
    return right;
}

std::string BinaryExpression::getOperator() const
{
    return op;
}

GroupingExpression::GroupingExpression(Expression* expression) : expression(expression) {}

Expression* GroupingExpression::getExpression() const
{
    return expression;
}

LiteralExpression::LiteralExpression(const std::string& value) : value(value) {}

std::string LiteralExpression::getValue() const
{
    return value;
}

UnaryExpression::UnaryExpression(const std::string& op, Expression* right) : op(op), right(right) {}

std::string UnaryExpression::getOperator() const
{
    return op;
}

Expression* UnaryExpression::getRight() const
{
    return right;
}