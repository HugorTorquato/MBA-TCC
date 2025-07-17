#include "../../../src/ProcessSourceFiles/Scanner/Scanner.h"

#include <gtest/gtest.h>

class ScannerTest : public ::testing::Test
{
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ScannerTest, ScanTokens_EmptyInput)
{
    std::string code = "";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_TRUE(tokens.empty());
}

TEST_F(ScannerTest, ScanTokens_WhiteSpaceInput)
{
    std::string code = "   ";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_TRUE(tokens.empty());
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_LEFT_PAREN)
{
    std::string code = "(";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "LEFT_PAREN");
    EXPECT_EQ(tokens[0]->getLexeme(), "(");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_RIGHT_PAREN)
{
    std::string code = ")";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "RIGHT_PAREN");
    EXPECT_EQ(tokens[0]->getLexeme(), ")");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_LEFT_BRACE)
{
    std::string code = "{";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "LEFT_BRACE");
    EXPECT_EQ(tokens[0]->getLexeme(), "{");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_RIGHT_BRACE)
{
    std::string code = "}";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "RIGHT_BRACE");
    EXPECT_EQ(tokens[0]->getLexeme(), "}");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_COMMA)
{
    std::string code = ",";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "COMMA");
    EXPECT_EQ(tokens[0]->getLexeme(), ",");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_DOT)
{
    std::string code = ".";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "DOT");
    EXPECT_EQ(tokens[0]->getLexeme(), ".");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_MINUS)
{
    std::string code = "-";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "MINUS");
    EXPECT_EQ(tokens[0]->getLexeme(), "-");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_PLUS)
{
    std::string code = "+";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "PLUS");
    EXPECT_EQ(tokens[0]->getLexeme(), "+");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_SEMICOLON)
{
    std::string code = ";";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "SEMICOLON");
    EXPECT_EQ(tokens[0]->getLexeme(), ";");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_STAR)
{
    std::string code = "*";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "STAR");
    EXPECT_EQ(tokens[0]->getLexeme(), "*");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_BANG)
{
    std::string code = "!";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "BANG");
    EXPECT_EQ(tokens[0]->getLexeme(), "!");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_BANG_EQUAL)
{
    std::string code = "!=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "BANG_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "!=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_EQUAL)
{
    std::string code = "=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_EQUAL_EQUAL)
{
    std::string code = "==";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "EQUAL_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "==");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_GREATER)
{
    std::string code = ">";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "GREATER");
    EXPECT_EQ(tokens[0]->getLexeme(), ">");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_GREATER_EQUAL)
{
    std::string code = ">=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "GREATER_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), ">=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_LESS)
{
    std::string code = "<";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "LESS");
    EXPECT_EQ(tokens[0]->getLexeme(), "<");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_LESS_EQUAL)
{
    std::string code = "<=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "LESS_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "<=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_SLASH)
{
    std::string code = "/";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "SLASH");
    EXPECT_EQ(tokens[0]->getLexeme(), "/");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanToken_SLASH_SLASH_Do_Not_Add_Comments_To_Token_Vector)
{
    std::string code = "//";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 0);
}

// MULTILINEcomment
TEST_F(ScannerTest, ScanTokens_SLASH_STAR_Do_Not_Add_Comments_To_Token_Vector)
{
    std::string code = "/* comment */";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 0);
}

TEST_F(ScannerTest, ScanTokens_MultiLineComment_SLASH_STAR_Do_Not_Add_Comments_To_Token_Vector)
{
    std::string code = "/*\n*/";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 0);
}

TEST_F(ScannerTest, ScanTokens_lineBreak)
{
    std::string code = "<\n>";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "LESS");
    EXPECT_EQ(tokens[0]->getLexeme(), "<");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[1]->getType(), "GREATER");
    EXPECT_EQ(tokens[1]->getLexeme(), ">");
    EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 2, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Multiple_Single_Char_and_comment_code_to_scann)
{
    std::string code = "(( )){} // grouping stuff";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);
    ASSERT_EQ(tokens.size(), 6);
    EXPECT_EQ(tokens[0]->getType(), "LEFT_PAREN");
    EXPECT_EQ(tokens[0]->getLexeme(), "(");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[1]->getType(), "LEFT_PAREN");
    EXPECT_EQ(tokens[1]->getLexeme(), "(");
    EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 1, Col: 2, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[2]->getType(), "RIGHT_PAREN");
    EXPECT_EQ(tokens[2]->getLexeme(), ")");
    EXPECT_EQ(tokens[2]->getLineFile(), "[LineFile] Line: 1, Col: 4, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[3]->getType(), "RIGHT_PAREN");
    EXPECT_EQ(tokens[3]->getLexeme(), ")");
    EXPECT_EQ(tokens[3]->getLineFile(), "[LineFile] Line: 1, Col: 5, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[4]->getType(), "LEFT_BRACE");
    EXPECT_EQ(tokens[4]->getLexeme(), "{");
    EXPECT_EQ(tokens[4]->getLineFile(), "[LineFile] Line: 1, Col: 6, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[5]->getType(), "RIGHT_BRACE");
    EXPECT_EQ(tokens[5]->getLexeme(), "}");
    EXPECT_EQ(tokens[5]->getLineFile(), "[LineFile] Line: 1, Col: 7, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Multiple_Single_and_Two_Char_and_comment_code_to_scann)
{
    std::string code = "!*+-/=<> <= == // operators";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 10);
    EXPECT_EQ(tokens[0]->getType(), "BANG");
    EXPECT_EQ(tokens[0]->getLexeme(), "!");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[1]->getType(), "STAR");
    EXPECT_EQ(tokens[1]->getLexeme(), "*");
    EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 1, Col: 2, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[2]->getType(), "PLUS");
    EXPECT_EQ(tokens[2]->getLexeme(), "+");
    EXPECT_EQ(tokens[2]->getLineFile(), "[LineFile] Line: 1, Col: 3, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[3]->getType(), "MINUS");
    EXPECT_EQ(tokens[3]->getLexeme(), "-");
    EXPECT_EQ(tokens[3]->getLineFile(), "[LineFile] Line: 1, Col: 4, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[4]->getType(), "SLASH");
    EXPECT_EQ(tokens[4]->getLexeme(), "/");
    EXPECT_EQ(tokens[4]->getLineFile(), "[LineFile] Line: 1, Col: 5, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[5]->getType(), "EQUAL");
    EXPECT_EQ(tokens[5]->getLexeme(), "=");
    EXPECT_EQ(tokens[5]->getLineFile(), "[LineFile] Line: 1, Col: 6, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[6]->getType(), "LESS");
    EXPECT_EQ(tokens[6]->getLexeme(), "<");
    EXPECT_EQ(tokens[6]->getLineFile(), "[LineFile] Line: 1, Col: 7, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[7]->getType(), "GREATER");
    EXPECT_EQ(tokens[7]->getLexeme(), ">");
    EXPECT_EQ(tokens[7]->getLineFile(), "[LineFile] Line: 1, Col: 8, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[8]->getType(), "LESS_EQUAL");
    EXPECT_EQ(tokens[8]->getLexeme(), "<=");
    EXPECT_EQ(tokens[8]->getLineFile(), "[LineFile] Line: 1, Col: 10, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[9]->getType(), "EQUAL_EQUAL");
    EXPECT_EQ(tokens[9]->getLexeme(), "==");
    EXPECT_EQ(tokens[9]->getLineFile(), "[LineFile] Line: 1, Col: 12, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_STRING)
{
    std::string code = "\"x\"";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "STRING");
    EXPECT_EQ(tokens[0]->getLexeme(), "x");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_MultiCharacter_STRING)
{
    std::string code = "\"Hello\"";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "STRING");
    EXPECT_EQ(tokens[0]->getLexeme(), "Hello");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_MultiLine_STRING)
{
    std::string code = "\"Hello\nWorld\"";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "STRING");
    EXPECT_EQ(tokens[0]->getLexeme(), "Hello\nWorld");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Unterminated_STRING)
{
    std::string code = "\"Hello";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);  // Expect no tokens due to unterminated string
    EXPECT_EQ(tokens[0]->getType(), "UNKNOWN");
    EXPECT_EQ(tokens[0]->getLexeme(), "");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

// Too much noisy
// TEST_F(ScannerTest, ScanTokens_ComplexCode)
// {
//     std::string code =
//         "int main() {\n"
//         "    std::cout << \"Hello, World!\";\n"
//         "    return;\n"
//         "}\n";
//     Scanner scanner(code);

//     std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

//     ASSERT_GT(tokens.size(), 0);  // Expect some tokens to be generated
//     // Additional checks can be added here for specific tokens if needed

//     // [Scanner][logTokens]Token Type: LEFT_PAREN, Lexeme: (, LineFile: [LineFile] Line: 1, Col:
//     9,
//     // End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[0]->getType(), "LEFT_PAREN");
//     EXPECT_EQ(tokens[0]->getLexeme(), "(");
//     EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 9, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: RIGHT_PAREN, Lexeme: ), LineFile: [LineFile] Line: 1, Col:
//     // 10, End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[1]->getType(), "RIGHT_PAREN");
//     EXPECT_EQ(tokens[1]->getLexeme(), ")");
//     EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 1, Col: 10, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: LEFT_BRACE, Lexeme: {, LineFile: [LineFile] Line: 1, Col:
//     12,
//     // End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[2]->getType(), "LEFT_BRACE");
//     EXPECT_EQ(tokens[2]->getLexeme(), "{");
//     EXPECT_EQ(tokens[2]->getLineFile(), "[LineFile] Line: 1, Col: 12, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: RIGHT_BRACE, Lexeme: }, LineFile: [LineFile] Line: 1, Col:
//     // 13, End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[3]->getType(), "RIGHT_BRACE");
//     EXPECT_EQ(tokens[3]->getLexeme(), "}");
//     EXPECT_EQ(tokens[3]->getLineFile(), "[LineFile] Line: 1, Col: 13, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: LESS, Lexeme: <, LineFile: [LineFile] Line: 2, Col: 15,
//     End
//     // Line: 0, End Col: 0
//     EXPECT_EQ(tokens[4]->getType(), "LESS");
//     EXPECT_EQ(tokens[4]->getLexeme(), "<");
//     EXPECT_EQ(tokens[4]->getLineFile(), "[LineFile] Line: 2, Col: 15, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: LESS, Lexeme: <, LineFile: [LineFile] Line: 2, Col: 16,
//     End
//     // Line: 0, End Col: 0
//     EXPECT_EQ(tokens[5]->getType(), "LESS");
//     EXPECT_EQ(tokens[5]->getLexeme(), "<");
//     EXPECT_EQ(tokens[5]->getLineFile(), "[LineFile] Line: 2, Col: 16, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: STRING, Lexeme: Hello, World!, LineFile: [LineFile] Line:
//     2,
//     // Col: 18, End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[6]->getType(), "STRING");
//     EXPECT_EQ(tokens[6]->getLexeme(), "Hello, World!");
//     EXPECT_EQ(tokens[6]->getLineFile(), "[LineFile] Line: 2, Col: 18, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: SEMICOLON, Lexeme: ;, LineFile: [LineFile] Line: 2, Col:
//     19,
//     // End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[7]->getType(), "SEMICOLON");
//     EXPECT_EQ(tokens[7]->getLexeme(), ";");
//     EXPECT_EQ(tokens[7]->getLineFile(), "[LineFile] Line: 2, Col: 19, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: SEMICOLON, Lexeme: ;, LineFile: [LineFile] Line: 3, Col:
//     13,
//     // End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[8]->getType(), "SEMICOLON");
//     EXPECT_EQ(tokens[8]->getLexeme(), ";");
//     EXPECT_EQ(tokens[8]->getLineFile(), "[LineFile] Line: 3, Col: 11, End Line: 0, End Col: 0");
//     // [Scanner][logTokens]Token Type: RIGHT_BRACE, Lexeme: }, LineFile: [LineFile] Line: 4, Col:
//     1,
//     // End Line: 0, End Col: 0
//     EXPECT_EQ(tokens[9]->getType(), "RIGHT_BRACE");
//     EXPECT_EQ(tokens[9]->getLexeme(), "}");
//     EXPECT_EQ(tokens[9]->getLineFile(), "[LineFile] Line: 4, Col: 1, End Line: 0, End Col: 0");
// }

// numbers
TEST_F(ScannerTest, ScanTokens_SingleDigitNumber)
{
    std::string code = "5";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "5");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_MultiDigitNumber)
{
    std::string code = "12345";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "12345");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_NumberWithDecimal)
{
    std::string code = "3.14";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "3.14");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_NumberWithNoDecimalButContinsDot)
{
    std::string code = "3.";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "3");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

// TEST_F(ScannerTest, ScanTokens_NumberWithLeadingDecimal)
// {
//     std::string code = ".456";
//     Scanner scanner(code);

//     std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code);

//     ASSERT_EQ(tokens.size(), 1);
//     EXPECT_EQ(tokens[0]->getType(), "NUMBER");
//     EXPECT_EQ(tokens[0]->getLexeme(), ".456");
//     EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
// }
