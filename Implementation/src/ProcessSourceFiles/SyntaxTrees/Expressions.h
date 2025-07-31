#pragma once

#include <string>

#include "IPrettyPrintVisitor.h"

class Expression
{
   public:
    virtual ~Expression() = default;
    virtual std::string accept(class IPrettyPrintVisitor* visitor) = 0;
};

// "Binary : Expr left, Token operator, Expr right",
class BinaryExpression : public Expression
{
   public:
    BinaryExpression(Expression* left, Expression* right, const std::string& op);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitBinaryExpression(this);
    }

    Expression* getLeft() const
    {
        return left;
    }
    Expression* getRight() const
    {
        return right;
    }
    std::string getOperator() const
    {
        return op;
    }

   private:
    Expression* left;
    Expression* right;
    std::string op;
};

// "Grouping : Expr expression",
class GroupingExpression : public Expression
{
   public:
    GroupingExpression(Expression* expression);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitGroupingExpression(this);
    }

    Expression* getExpression() const
    {
        return expression;
    }

   private:
    Expression* expression;
};

// "Literal : Object value",
class LiteralExpression : public Expression
{
   public:
    LiteralExpression(const std::string& value);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitLiteralExpression(this);
    }

    std::string getValue() const
    {
        return value;
    }

   private:
    std::string value;
};

// "Unary : Token operator, Expr right"
class UnaryExpression : public Expression
{
   public:
    UnaryExpression(const std::string& op, Expression* right);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitUnaryExpression(this);
    }

    std::string getOperator() const
    {
        return op;
    }
    Expression* getRight() const
    {
        return right;
    }

   private:
    std::string op;
    Expression* right;
};