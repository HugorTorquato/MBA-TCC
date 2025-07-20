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
    if (!isAtEndOfSource(sourceCode.length(), current) && sourceCode[current] == '\n')
    {
        line++;
        // Reset column to 0 for the new line -> Return to 0 because the new line char will count as
        // a col. So we expect to add 1 in the scanner
        col = 0;
        Logger::getInstance().log(
            "[Scanner][updateCurrentAndLineFiles] New line detected. Incrementing line number and "
            "resetting column.");
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

// One char of loo ahead. The smaller this number is the faster the scanner runs.
bool match(const char expected, const int sourceLength, const int current,
           const std::string& sourceCode)
{
    const int next = current + 1;

    if (isAtEndOfSource(sourceLength, next))
    {
        Logger::getInstance().log("[Scanner][match] No more characters to match.");
        return false;
    }
    Logger::getInstance().log("[Scanner][match] Matching character: " + std::string(1, expected) +
                              " with source code: " + std::string(1, sourceCode[next]) +
                              " at index: " + std::to_string(next));
    if (expected != sourceCode[next])
    {
        Logger::getInstance().log(
            "[Scanner][match] Expected character: " + std::string(1, expected) +
            ", but found: " + std::string(1, sourceCode[next]));
        return false;
    }
    return true;
}

void logTokens(const std::vector<std::shared_ptr<IToken>>& tokens)
{
    for (const auto token : tokens)
    {
        Logger::getInstance().log("[Scanner][logTokens]" + token->toString());
    }
}

std::string stringLiterals(const std::string& sourceCode, int& current, int& line, int& col)
{
    Logger::getInstance().log("[Scanner][stringLiterals] Starting to scan string literals.");
    std::string lexeme;

    while (isAtEndOfSource(sourceCode.length(), current) == false &&
           match('"', sourceCode.length(), current, sourceCode) == false)
    {
        current++;  // Consume the current character
        // TODO: This would be useful for endl line and col variables
        // if (match('\n', sourceCode.length(), current, sourceCode))
        // {
        //     line++;
        //     col = 0;
        // }
        // else
        // {
        //     col++;
        // }
        Logger::getInstance().log(
            "[Scanner][stringLiterals] Current character: " + std::string(1, sourceCode[current]) +
            " at index: " + std::to_string(current));
        lexeme += sourceCode[current];
    }

    if (isAtEndOfSource(sourceCode.length(), current))
    {
        Logger::getInstance().log("[Scanner][stringLiterals] Unterminated string literal.");
        return "";  // Unterminated string literal
    }

    current++;  // Consume the closing '"'
    return lexeme;
}

bool isAnyDigit(char c)
{
    // TODO: Add support for hex, octal, binary literals, and special cases like .1234 and 1234.
    return c >= '0' && c <= '9';
}

void populateLexemeWithNumbers(const std::string& sourceCode, int& current, std::string& lexeme)
{
    Logger::getInstance().log(
        "[Scanner][numberLiterals][populateLexemeWithNumbers] current: " + std::to_string(current) +
        " current character: " + std::string(1, sourceCode[current]));
    while (isAtEndOfSource(sourceCode.length(), current) == false &&
           isAnyDigit(sourceCode[current]))
    {
        Logger::getInstance().log(
            "[Scanner][numberLiterals][populateLexemeWithNumbers] Current number: " +
            std::string(1, sourceCode[current]) + " at index: " + std::to_string(current));
        lexeme += sourceCode[current];
        current++;  // Consume the current character
    }
}

std::string numberLiterals(const std::string& sourceCode, int& current, int& line, int& col)
{
    Logger::getInstance().log("[Scanner][numberLiterals] Starting to scan number literals.");
    std::string lexeme;

    populateLexemeWithNumbers(sourceCode, current, lexeme);

    Logger::getInstance().log("[Scanner][numberLiterals] Number literal found: " + lexeme +
                              " at index: " + std::to_string(current) +
                              " current character: " + std::string(1, sourceCode[current]));

    if (sourceCode[current] == '.' && isAnyDigit(sourceCode[current + 1]))
    {
        // We don't want to consume the . until we have at least one digit after it.
        lexeme += ".";
        current++;
        populateLexemeWithNumbers(sourceCode, current, lexeme);

        Logger::getInstance().log("[Scanner][numberLiterals] Number literal found with decimal: " +
                                  lexeme + " at index: " + std::to_string(current) +
                                  " current character: " + std::string(1, sourceCode[current]));
    }

    return lexeme;
}

bool isAnyAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

std::string identifierLiterals(const std::string& sourceCode, int& current, int& line, int& col)
{
    Logger::getInstance().log(
        "[Scanner][identifierLiterals] Starting to scan identifier literals.");
    std::string lexeme;

    // Consume the first character
    lexeme += sourceCode[current];
    current++;  // Move to the next character

    while (isAtEndOfSource(sourceCode.length(), current) == false &&
           (isAnyAlpha(sourceCode[current]) || isAnyDigit(sourceCode[current])))
    {
        Logger::getInstance().log("[Scanner][identifierLiterals] Current identifier character: " +
                                  std::string(1, sourceCode[current]) +
                                  " at index: " + std::to_string(current));
        lexeme += sourceCode[current];
        current++;  // Consume the current character
    }

    return lexeme;
}
}  // namespace

Scanner::Scanner(const std::string& sourceCode) : m_sourceCode(sourceCode)
{
    Logger::getInstance().log("[Scanner][Scanner] Initialized with source code.");
}

void Scanner::scanToken(const std::string& sourceCode, int& start, int& current, int& line,
                        int& col)
{
    const int sourceLength = sourceCode.length();

    // Start simple, with lexemes of only one character.
    // we need to consume a token type and pick a token type for it

    char currentChar = sourceCode[current];
    Logger::getInstance().log("[Scanner][scanToken] Current character: " +
                              std::string(1, currentChar));

    // TODO: Include missing tokens as we found
    switch (currentChar)
    {
        // TODO:
        // case '<<':
        // case '>>':
        // case '&&':
        // case '||':
        // case '++':
        // case '--':
        // case '::':
        // case '->':
        // case '??':
        // case '??=':
        // case '::=':
        // case '=>':
        // case '...':
        // case '??':

        //
        // ignore white spaces
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            Logger::getInstance().log(
                "[Scanner][scanToken] Ignore invalid chars from been added to the token vector.");
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
            // if (!isAtEndOfSource(sourceLength, current) && isAnyDigit(sourceCode[current + 1]))
            // {
            //     // This is a number starting with . and not a real DOT ( .1234)
            //     break;
            // }
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
        // 2 char operators
        case '!':
            if (match('=', sourceLength, current, sourceCode))
            {
                addToken(TokenType::BANG_EQUAL, m_tokens, "!=", line, col);
                current++;  // Consume the '=' character
            }
            else
            {
                addToken(TokenType::BANG, m_tokens, "!", line, col);
            }
            break;
        case '=':
            if (match('=', sourceLength, current, sourceCode))
            {
                addToken(TokenType::EQUAL_EQUAL, m_tokens, "==", line, col);
                current++;  // Consume the '=' character
            }
            else
            {
                addToken(TokenType::EQUAL, m_tokens, "=", line, col);
            }
            break;
        case '>':
            if (match('=', sourceLength, current, sourceCode))
            {
                addToken(TokenType::GREATER_EQUAL, m_tokens, ">=", line, col);
                current++;  // Consume the '=' character
            }
            else
            {
                addToken(TokenType::GREATER, m_tokens, ">", line, col);
            }
            break;
        case '<':
            if (match('=', sourceLength, current, sourceCode))
            {
                addToken(TokenType::LESS_EQUAL, m_tokens, "<=", line, col);
                current++;  // Consume the '=' character
            }
            else
            {
                addToken(TokenType::LESS, m_tokens, "<", line, col);
            }
            break;

        // Longer Lexemes
        case '/':
            // Check for comments. They are lexemes but not meaningful tokens. The parser doesn't
            // want to deal with them. So we don't add them to the token vector.
            if (match('/', sourceLength, current, sourceCode))
            {
                // Single-line comment
                while (!isAtEndOfSource(sourceLength, current) && sourceCode[current] != '\n')
                {
                    current++;
                }
            }
            else if (match('*', sourceLength, current, sourceCode))
            {
                // Multi-line comment
                while (
                    !isAtEndOfSource(sourceLength, current) &&
                    !(sourceCode[current] == '*' && match('/', sourceLength, current, sourceCode)))
                {
                    if (sourceCode[current] == '\n')
                    {
                        line++;
                        col = 1;
                    }
                    current++;
                }
                // Consume the closing '*/'
                if (!isAtEndOfSource(sourceLength, current))
                {
                    current += 2;  // Skip '*/'
                }
            }
            // Only add single slash tokens if they are not part of a comment ( division )
            else
            {
                addToken(TokenType::SLASH, m_tokens, "/", line, col);
            }
            break;
        // String Literals
        case '"':
        {
            auto lexeme = stringLiterals(sourceCode, current, line, col);
            addToken(TokenType::STRING, m_tokens, lexeme, line, col);
            break;
        }

        default:
            // Number Literals
            //  A number literal is a series of digits optionally followed by . a and one or more
            //  trailing digits
            //  TODO: Special cases .1234 1234.
            if (isAnyDigit(currentChar))
            {
                auto lexeme = numberLiterals(sourceCode, current, line, col);
                addToken(TokenType::NUMBER, m_tokens, lexeme, line, col);
                break;
            }
            // Identifiers and Keywords ( Reserved words )
            else if (isAnyAlpha(currentChar))
            {
                auto lexeme = identifierLiterals(sourceCode, current, line, col);

                // Check if the lexeme is a keyword
                auto it = TokenTypeNameSpace::keywordsMap.find(lexeme);
                if (it != TokenTypeNameSpace::keywordsMap.end())
                {
                    Logger::getInstance().log("[Scanner][scanToken] keyword found: " + lexeme +
                                              " at line: " + std::to_string(line) +
                                              ", col: " + std::to_string(col));
                    addToken(it->second, m_tokens, lexeme, line, col);
                    break;
                }

                Logger::getInstance().log("[Scanner][scanToken] Identifier found: " + lexeme +
                                          " at line: " + std::to_string(line) +
                                          ", col: " + std::to_string(col));
                addToken(TokenType::IDENTIFIER, m_tokens, lexeme, line, col);
                break;
            }
            else
            {
                // May be good to comment this for large source code files
                Logger::getInstance().log(
                    "[Scanner][scanToken] Unrecognized character: " + std::string(1, currentChar) +
                    " at line: " + std::to_string(line) + ", col: " + std::to_string(col));
            }
            break;
    }

    updateCurrentAndLineFiles(sourceCode, current, line, col);
}

std::vector<std::shared_ptr<IToken>> Scanner::scanTokens(const std::string& rawSourceCode)
{
    Logger::getInstance().log("[Scanner][scanTokens] rawSourceCode: " + rawSourceCode);
    if (!isValidSourceCode(rawSourceCode)) return {};

    m_tokens.clear();  // Clear to avoid issues reusing the scanToken method

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

    logTokens(m_tokens);  // Only for Debug - REMOVE

    return m_tokens;
}
