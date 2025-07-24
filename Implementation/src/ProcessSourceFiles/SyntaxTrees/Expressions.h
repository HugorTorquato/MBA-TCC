#pragma once

#include <string>

#include "IVisitor.h"

class Expression
{
    virtual ~Expression() = default;
    virtual void accept(class IVisitor* visitor) = 0;
};

// "Binary : Expr left, Token operator, Expr right",
class BinaryExpression : public Expression
{
    BinaryExpression(Expression* left, Expression* right, const std::string& op);
    ~BinaryExpression();

    void accept(IVisitor* visitor) override
    {
        visitor->visitBinaryExpression(this);
    }

   private:
    Expression* left;
    Expression* right;
    std::string op;
};

// "Grouping : Expr expression",
class GroupingExpression : public Expression
{
    GroupingExpression(Expression* expression);
    ~GroupingExpression();          

    void accept(IVisitor* visitor) override
    {
        visitor->visitGroupingExpression(this);
    }

   private:
    Expression* expression;
};

// "Literal : Object value",
class LiteralExpression : public Expression
{
    LiteralExpression(const std::string& value);
    ~LiteralExpression();

    void accept(IVisitor* visitor) override
    {
        visitor->visitLiteralExpression(this);
    }

   private:
    std::string value;
};

// "Unary : Token operator, Expr right"
class UnaryExpression : public Expression
{
    UnaryExpression(const std::string& op, Expression* right);
    ~UnaryExpression();

    void accept(IVisitor* visitor) override
    {
        visitor->visitUnaryExpression(this);
    }

   private:
    std::string op;
    Expression* right;
};