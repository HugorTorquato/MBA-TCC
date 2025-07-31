#pragma once

#include <string>

#include "IPrettyPrintVisitor.h"

class PrettyPrintVisitor : public IPrettyPrintVisitor
{
   public:
    std::string visitBinaryExpression(BinaryExpression* expr) override;
    std::string visitGroupingExpression(GroupingExpression* expr) override;
    std::string visitLiteralExpression(LiteralExpression* expr) override;
    std::string visitUnaryExpression(UnaryExpression* expr) override;

    // Add more visit methods as needed for other node types.
};
