#include "Scanner.h"

#include <string>

#include "../../Logger/Log.h"
#include "Token.h"

namespace
{
// Helper functions to validate the source code and check for end of source
bool isValidSourceCode(const std::string& sourceCode)
{
    if (sourceCode.empty())
    {
        Logger::getInstance().log("[Scanner][isValidSourceCode] rawSourceCode is empty");
        return false;
    }

    return true;
}

// Helper function that tells us if we’ve consumed all the characters
bool isAtEndOfSource(int sourceLength, int currentIndex)
{
    if (currentIndex >= sourceLength)
    {
        Logger::getInstance().log("[Scanner][isAtEndOfSource] Reached end of source code.");
        return true;
    }
    return false;
}

void updateCurrentAndLineFiles(const std::string& sourceCode, int& current, int& line, int& col)
{
    // Update the current index, line, and column based on the current character
    current++;
    col++;

    // If we encounter a newline character, we should increment the line number and reset the column
    if (isAtEndOfSource(sourceCode.length(), current) && sourceCode[current] == '\n')
    {
        line++;
        col = 1;  // Reset column to 1 for the new line
    }

    Logger::getInstance().log(
        "[Scanner][updateCurrentAndLineFiles] Current: " + std::to_string(current) +
        ", Line: " + std::to_string(line) + ", Col: " + std::to_string(col));
}

void addToken(TokenType type, std::vector<std::shared_ptr<IToken>>& tokens,
              const std::string& lexeme, int line, int col)
{
    // TODO: May need to come back and refactor this function to handle end line and column ( hard
    // codded to zero for now)
    tokens.push_back(std::make_shared<Token>(type, lexeme, LineFile(line, col, 0, 0)));
    Logger::getInstance().log("[Scanner][addToken] Added token: " + lexeme);
}

}  // namespace

Scanner::Scanner(const std::string& sourceCode) : m_sourceCode(sourceCode)
{
    Logger::getInstance().log("[Scanner][Scanner] Initialized with source code.");
}

void Scanner::scanToken(const std::string& sourceCode, int& start, int& current, int& line,
                        int& col)
{
    // Start simple, with lexemes of only one character.
    // we need to consume a token type and pick a token type for it

    char currentChar = sourceCode[current];
    Logger::getInstance().log("[Scanner][scanToken] Current character: " +
                              std::string(1, currentChar));

    // TODO: Include missing tokens as we found
    switch (currentChar)
    {
        // ignore white spaces
        case ' ':
        case '\n':
        case '\t':
            Logger::getInstance().log("[Scanner][scanToken] Ignore invalid chars from been added to the token vector.");
            break;
        // Single char tokens
        case '(':
            addToken(TokenType::LEFT_PAREN, m_tokens, "(", line, col);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN, m_tokens, ")", line, col);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE, m_tokens, "{", line, col);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE, m_tokens, "}", line, col);
            break;
        case ',':
            addToken(TokenType::COMMA, m_tokens, ",", line, col);
            break;
        case '.':
            addToken(TokenType::DOT, m_tokens, ".", line, col);
            break;
        case '-':
            addToken(TokenType::MINUS, m_tokens, "-", line, col);
            break;
        case '+':
            addToken(TokenType::PLUS, m_tokens, "+", line, col);
            break;
        case ';':
            addToken(TokenType::SEMICOLON, m_tokens, ";", line, col);
            break;
        case '*':
            addToken(TokenType::STAR, m_tokens, "*", line, col);
            break;

        default:
            // May be good to comment this for large source code files
            Logger::getInstance().log(
                "[Scanner][scanToken] Unrecognized character: " + std::string(1, currentChar) +
                " at line: " + std::to_string(line) + ", col: " + std::to_string(col));
            break;
    }

    updateCurrentAndLineFiles(sourceCode, current, line, col);
}

std::vector<std::shared_ptr<IToken>> Scanner::scanTokens(const std::string& rawSourceCode)
{
    Logger::getInstance().log("[Scanner][scanTokens] rawSourceCode: " + rawSourceCode);
    if (!isValidSourceCode(rawSourceCode)) return {};

    // TODO: Implement logic for end line and col
    int start = 0;    // Start index of the current lexeme
    int current = 0;  // Current index in the source code
    int line = 1;     // Current line number
    int col = 1;      // Current column number

    const int rawSourceCodeLength = rawSourceCode.length();

    // Loop into all chars from source code
    while (!isAtEndOfSource(rawSourceCodeLength, current))
    {
        // At the beginning of the next lexeme
        // Each turn of the loop we scan a single token.
        Logger::getInstance().log("[Scanner][scanTokens] Scanning token at index: " +
                                  std::to_string(current));

        start = current;
        scanToken(rawSourceCode, start, current, line, col);
    }

    // m_tokens.push_back()

    return m_tokens;
}
