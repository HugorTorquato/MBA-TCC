#pragma once

#include <string>

#include "IPrettyPrintVisitor.h"

// TODO: A good exercise is to convert this to smart pointers and use them in the visitor
//   to avoid manual memory management. This will help prevent memory leaks and make the code safer.

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

    Expression* getLeft() const;
    Expression* getRight() const;
    std::string getOperator() const;

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

    Expression* getExpression() const;

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

    std::string getValue() const;

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

    std::string getOperator() const;
    Expression* getRight() const;

   private:
    std::string op;
    Expression* right;
};