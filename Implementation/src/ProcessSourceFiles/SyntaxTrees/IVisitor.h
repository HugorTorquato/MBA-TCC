#pragma once

class IVisitor
{
   public:
    virtual ~IVisitor() = default;

    // Visit methods for different syntax tree nodes.
    virtual void visitBinaryExpression(class BinaryExpression* expr) = 0;
    virtual void visitGroupingExpression(class GroupingExpression* expr) = 0;
    virtual void visitLiteralExpression(class LiteralExpression* expr) = 0;
    virtual void visitUnaryExpression(class UnaryExpression* expr) = 0;

    // Add more visit methods as needed for other node types.
};
// This interface can be extended to include more visit methods for different node types in the syntax tree.
// Each visit method should handle the specific logic for that type of expression, allowing for polymorphic
// behavior when traversing the syntax tree.
// The implementation of these methods would typically involve processing the expression and potentially
// generating code, evaluating the expression, or performing other operations based on the type of expression.