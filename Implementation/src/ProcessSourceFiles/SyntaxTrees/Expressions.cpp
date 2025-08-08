#include "Expressions.h"

BinaryExpression::BinaryExpression(std::shared_ptr<Expression> left,
                                   std::shared_ptr<Expression> right, const std::string& op)
    : left(left), right(right), op(op)
{
}

std::shared_ptr<Expression> BinaryExpression::getLeft() const
{
    return left;
}

std::shared_ptr<Expression> BinaryExpression::getRight() const
{
    return right;
}

std::string BinaryExpression::getOperator() const
{
    return op;
}

GroupingExpression::GroupingExpression(std::shared_ptr<Expression> expression)
    : expression(expression)
{
}

std::shared_ptr<Expression> GroupingExpression::getExpression() const
{
    return expression;
}

LiteralExpression::LiteralExpression(const std::string& value) : value(value) {}

std::string LiteralExpression::getValue() const
{
    return value;
}

UnaryExpression::UnaryExpression(const std::string& op, std::shared_ptr<Expression> right)
    : op(op), right(right)
{
}

std::string UnaryExpression::getOperator() const
{
    return op;
}

std::shared_ptr<Expression> UnaryExpression::getRight() const
{
    return right;
}