#pragma once

#include "CommonParserType.h"
#include "IPrettyPrintVisitor.h"

class Expression : public CommonParserType
{
   public:
    virtual std::string accept(class IPrettyPrintVisitor* visitor) override = 0;
    virtual std::string getType() const override = 0;
};

// "Binary : Expr left, Token operator, Expr right",
class BinaryExpression : public Expression
{
   public:
    BinaryExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right,
                     std::shared_ptr<IToken> op);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitBinaryExpression(this);
    }

    std::shared_ptr<Expression> getLeft() const;
    std::shared_ptr<Expression> getRight() const;
    std::string getOperator() const;
    std::string getType() const override
    {
        return "BINARY_EXPRESSION";
    }

   private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    std::shared_ptr<IToken> op;
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
    std::string getType() const override
    {
        return "GROUPING_EXPRESSION";
    }

   private:
    std::shared_ptr<Expression> expression;
};

// "Literal : Object value",
class LiteralExpression : public Expression
{
   public:
    LiteralExpression(std::shared_ptr<IToken> value);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitLiteralExpression(this);
    }

    std::string getValue() const;
    std::string getType() const override
    {
        return "LITERAL_EXPRESSION";
    }
    // std::string getLexeme() const { return value->getLexeme(); }

   private:
    std::shared_ptr<IToken> value;
};

// "Unary : Token operator, Expr right"
class UnaryExpression : public Expression
{
   public:
    UnaryExpression(std::shared_ptr<IToken> op, std::shared_ptr<Expression> right);

    std::string accept(IPrettyPrintVisitor* visitor) override
    {
        return visitor->visitUnaryExpression(this);
    }

    std::string getOperator() const;
    std::shared_ptr<Expression> getRight() const;
    std::string getType() const override
    {
        return "UNARY_EXPRESSION";
    }

   private:
    std::shared_ptr<IToken> op;
    std::shared_ptr<Expression> right;
};