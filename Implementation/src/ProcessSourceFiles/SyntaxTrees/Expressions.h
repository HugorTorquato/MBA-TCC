#pragma once

#include <memory>
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
    BinaryExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right,
                     const std::string& op);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitBinaryExpression(this);
    }

    std::shared_ptr<Expression> getLeft() const;
    std::shared_ptr<Expression> getRight() const;
    std::string getOperator() const;

   private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    std::string op;
};

// "Grouping : Expr expression",
class GroupingExpression : public Expression
{
   public:
    GroupingExpression(std::shared_ptr<Expression> expression);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitGroupingExpression(this);
    }

    std::shared_ptr<Expression> getExpression() const;

   private:
    std::shared_ptr<Expression> expression;
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
    UnaryExpression(const std::string& op, std::shared_ptr<Expression> right);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitUnaryExpression(this);
    }

    std::string getOperator() const;
    std::shared_ptr<Expression> getRight() const;

   private:
    std::string op;
    std::shared_ptr<Expression> right;
};