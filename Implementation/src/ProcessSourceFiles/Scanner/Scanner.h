#pragma once

#include "IScanner.h"

class Scanner : public IScanner
{
   public:
    Scanner(const std::string& sourceCode);

    // Vector is faster to acess over it. List is faster to add and remove items.
    // Use vector for the list of tokens, as it is more efficient for access patterns.
    std::vector<std::shared_ptr<IToken>> scanTokens(const std::string& rawSourceCode,
                                                    const std::string& fileName) override;

   private:
    // The real heart of the scanner.
    void scanToken(const std::string& sourceCode, int& start, int& current, int& line, int& col,
                   const std::string& fileName);

   private:
    std::string m_sourceCode;  // Store the source code to be scanned
    // You should store a list of std::shared_ptr<IToken> in your Scanner class, not the concrete
    // Token objects.
    std::vector<std::shared_ptr<IToken>>
        m_tokens;  // Vector of tokens generated from the source code
};