#include "Expressions.h"

BinaryExpression::BinaryExpression(Expression* left, Expression* right, const std::string& op)
    : left(left), right(right), op(op)
{
}

GroupingExpression::GroupingExpression(Expression* expression) : expression(expression) {}

LiteralExpression::LiteralExpression(const std::string& value) : value(value) {}

UnaryExpression::UnaryExpression(const std::string& op, Expression* right) : op(op), right(right) {}