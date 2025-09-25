#include "../../../src/ProcessSourceFiles/Scanner/Scanner.h"

#include <gtest/gtest.h>

class ScannerTest : public ::testing::Test
{
   protected:
    const std::string m_fileName = "";
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ScannerTest, ScanTokens_EmptyInput)
{
    std::string code = "";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 0);
}

TEST_F(ScannerTest, ScanTokens_WhiteSpaceInput)
{
    std::string code = "   ";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0]->getType(), "END_OF_FILE");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_COMMA_WithFileName)
{
    std::string code = ",";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "COMMA");
    EXPECT_EQ(tokens[0]->getLexeme(), ",");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_DOT_WithFileName)
{
    std::string code = ".";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "DOT");
    EXPECT_EQ(tokens[0]->getLexeme(), ".");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_MINUS_WithFileName)
{
    std::string code = "-";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "MINUS");
    EXPECT_EQ(tokens[0]->getLexeme(), "-");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_PLUS_WithFileName)
{
    std::string code = "+";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "PLUS");
    EXPECT_EQ(tokens[0]->getLexeme(), "+");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_SEMICOLON_WithFileName)
{
    std::string code = ";";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "SEMICOLON");
    EXPECT_EQ(tokens[0]->getLexeme(), ";");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_STAR_WithFileName)
{
    std::string code = "*";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "STAR");
    EXPECT_EQ(tokens[0]->getLexeme(), "*");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_BANG_WithFileName)
{
    std::string code = "!";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "BANG");
    EXPECT_EQ(tokens[0]->getLexeme(), "!");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_EQUAL_WithFileName)
{
    std::string code = "=";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "=");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_SLASH_WithFileName)
{
    std::string code = "/";
    Scanner scanner(code);
    const std::string dummyFile = "FileToUseInScanner.cpp";

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, dummyFile);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "SLASH");
    EXPECT_EQ(tokens[0]->getLexeme(), "/");
    EXPECT_EQ(tokens[0]->getLineFile(),
              "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0 with file name: "
              "FileToUseInScanner.cpp");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_RIGHT_BRACE)
{
    std::string code = "}";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "RIGHT_BRACE");
    EXPECT_EQ(tokens[0]->getLexeme(), "}");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_COMMA)
{
    std::string code = ",";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "COMMA");
    EXPECT_EQ(tokens[0]->getLexeme(), ",");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_DOT)
{
    std::string code = ".";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "DOT");
    EXPECT_EQ(tokens[0]->getLexeme(), ".");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_MINUS)
{
    std::string code = "-";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "MINUS");
    EXPECT_EQ(tokens[0]->getLexeme(), "-");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_PLUS)
{
    std::string code = "+";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "PLUS");
    EXPECT_EQ(tokens[0]->getLexeme(), "+");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_SEMICOLON)
{
    std::string code = ";";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "SEMICOLON");
    EXPECT_EQ(tokens[0]->getLexeme(), ";");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_STAR)
{
    std::string code = "*";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "STAR");
    EXPECT_EQ(tokens[0]->getLexeme(), "*");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_BANG)
{
    std::string code = "!";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "BANG");
    EXPECT_EQ(tokens[0]->getLexeme(), "!");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_BANG_EQUAL)
{
    std::string code = "!=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "BANG_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "!=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_EQUAL)
{
    std::string code = "=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_EQUAL_EQUAL)
{
    std::string code = "==";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "EQUAL_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "==");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_GREATER)
{
    std::string code = ">";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "GREATER");
    EXPECT_EQ(tokens[0]->getLexeme(), ">");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_GREATER_EQUAL)
{
    std::string code = ">=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "GREATER_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), ">=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_LESS)
{
    std::string code = "<";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "LESS");
    EXPECT_EQ(tokens[0]->getLexeme(), "<");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_LESS_EQUAL)
{
    std::string code = "<=";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "LESS_EQUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "<=");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_SingleCharacter_SLASH)
{
    std::string code = "/";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "SLASH");
    EXPECT_EQ(tokens[0]->getLexeme(), "/");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanToken_SLASH_SLASH_Do_Not_Add_Comments_To_Token_Vector)
{
    std::string code = "//";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 1);
}

// MULTILINEcomment
TEST_F(ScannerTest, ScanTokens_SLASH_STAR_Do_Not_Add_Comments_To_Token_Vector)
{
    std::string code = "/* comment */";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 1);
}

TEST_F(ScannerTest, ScanTokens_MultiLineComment_SLASH_STAR_Do_Not_Add_Comments_To_Token_Vector)
{
    std::string code = "/*\n*/";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 1);
}

TEST_F(ScannerTest, ScanTokens_lineBreak)
{
    std::string code = "<\n>";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 3);
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

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);
    ASSERT_EQ(tokens.size(), 7);
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

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 11);
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

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "STRING");
    EXPECT_EQ(tokens[0]->getLexeme(), "x");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_MultiCharacter_STRING)
{
    std::string code = "\"Hello\"";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "STRING");
    EXPECT_EQ(tokens[0]->getLexeme(), "Hello");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_MultiLine_STRING)
{
    std::string code = "\"Hello\nWorld\"";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "STRING");
    EXPECT_EQ(tokens[0]->getLexeme(), "Hello\nWorld");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

// TODO: Need to scape in the class parser or handle it better in the scanner ( failing with full
// test ) TEST_F(ScannerTest, ScanTokens_Unterminated_STRING)
// {
//     std::string code = "\"Hello";
//     Scanner scanner(code);

//     std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

//     ASSERT_EQ(tokens.size(), 2);  // Expect no tokens due to unterminated string
//     EXPECT_EQ(tokens[0]->getType(), "UNKNOWN");
//     EXPECT_EQ(tokens[0]->getLexeme(), "");
//     EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
// }

// numbers
TEST_F(ScannerTest, ScanTokens_SingleDigitNumber)
{
    std::string code = "5";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "5");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_MultiDigitNumber)
{
    std::string code = "12345";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "12345");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_NumberWithDecimal)
{
    std::string code = "3.14";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "3.14");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

// TODO: Is it suppose to be 3.0 r 3? in this case i can't process the . token
TEST_F(ScannerTest, ScanTokens_NumberWithNoDecimalButContinsDot)
{
    std::string code = "3.";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "3");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[1]->getType(), "DOT");
    EXPECT_EQ(tokens[1]->getLexeme(), ".");
    EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 1, Col: 2, End Line: 0, End Col: 0");
}

// TEST_F(ScannerTest, ScanTokens_NumberWithLeadingDecimal)
// {
//     std::string code = ".456";
//     Scanner scanner(code);

//     std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

//     ASSERT_EQ(tokens.size(), 2);
//     EXPECT_EQ(tokens[0]->getType(), "NUMBER");
//     EXPECT_EQ(tokens[0]->getLexeme(), ".456");
//     EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
// }

TEST_F(ScannerTest, ScanTokens_NumberWithLeadingZero)
{
    std::string code = "0123";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "NUMBER");
    EXPECT_EQ(tokens[0]->getLexeme(), "0123");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

// Identifier
TEST_F(ScannerTest, ScanTokens_Identifier)
{
    std::string code = "variableName";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[0]->getLexeme(), "variableName");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_IdentifierWithNumbers)
{
    std::string code = "var123";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[0]->getLexeme(), "var123");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_IdentifierWithUnderscore)
{
    std::string code = "_varName";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[0]->getLexeme(), "_varName");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_IdentifierWithMixedCase)
{
    std::string code = "VarName";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[0]->getLexeme(), "VarName");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

// Keywords
TEST_F(ScannerTest, ScanTokens_Keyword_if)
{
    std::string code = "if";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "IF");
    EXPECT_EQ(tokens[0]->getLexeme(), "if");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_else)
{
    std::string code = "else";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "ELSE");
    EXPECT_EQ(tokens[0]->getLexeme(), "else");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_while)
{
    std::string code = "while";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "WHILE");
    EXPECT_EQ(tokens[0]->getLexeme(), "while");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_for)
{
    std::string code = "for";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "FOR");
    EXPECT_EQ(tokens[0]->getLexeme(), "for");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_return)
{
    std::string code = "return";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "RETURN");
    EXPECT_EQ(tokens[0]->getLexeme(), "return");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

// TEST_F(ScannerTest, ScanTokens_Keyword_class)
// {
//     std::string code = "class";
//     Scanner scanner(code);

//     std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

//     ASSERT_EQ(tokens.size(), 2);
//     EXPECT_EQ(tokens[0]->getType(), "CLASS");
//     EXPECT_EQ(tokens[0]->getLexeme(), "class");
//     EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
// }

TEST_F(ScannerTest, ScanTokens_Keyword_static)
{
    std::string code = "static";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "STATIC");
    EXPECT_EQ(tokens[0]->getLexeme(), "static");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_public)
{
    std::string code = "public";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "PUBLIC");
    EXPECT_EQ(tokens[0]->getLexeme(), "public");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_private)
{
    std::string code = "private";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "PRIVATE");
    EXPECT_EQ(tokens[0]->getLexeme(), "private");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_protected)
{
    std::string code = "protected";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "PROTECTED");
    EXPECT_EQ(tokens[0]->getLexeme(), "protected");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_new)
{
    std::string code = "new";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "NEW");
    EXPECT_EQ(tokens[0]->getLexeme(), "new");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_delete)
{
    std::string code = "delete";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "DELETE");
    EXPECT_EQ(tokens[0]->getLexeme(), "delete");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_void)
{
    std::string code = "void";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "VOID");
    EXPECT_EQ(tokens[0]->getLexeme(), "void");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_virtual)
{
    std::string code = "virtual";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "VIRTUAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "virtual");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_int)
{
    std::string code = "int";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "INT");
    EXPECT_EQ(tokens[0]->getLexeme(), "int");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_and)
{
    std::string code = "and";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "AND");
    EXPECT_EQ(tokens[0]->getLexeme(), "and");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_and_eq)
{
    std::string code = "and_eq";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "AND_EQ");
    EXPECT_EQ(tokens[0]->getLexeme(), "and_eq");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_asm)
{
    std::string code = "asm";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "ASM");
    EXPECT_EQ(tokens[0]->getLexeme(), "asm");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_auto)
{
    std::string code = "auto";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "AUTO");
    EXPECT_EQ(tokens[0]->getLexeme(), "auto");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_bitand)
{
    std::string code = "bitand";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "BITAND");
    EXPECT_EQ(tokens[0]->getLexeme(), "bitand");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_bitor)
{
    std::string code = "bitor";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "BITOR");
    EXPECT_EQ(tokens[0]->getLexeme(), "bitor");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_bool)
{
    std::string code = "bool";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "BOOL");
    EXPECT_EQ(tokens[0]->getLexeme(), "bool");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_break)
{
    std::string code = "break";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "BREAK");
    EXPECT_EQ(tokens[0]->getLexeme(), "break");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_case)
{
    std::string code = "case";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CASE");
    EXPECT_EQ(tokens[0]->getLexeme(), "case");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_catch)
{
    std::string code = "catch";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CATCH");
    EXPECT_EQ(tokens[0]->getLexeme(), "catch");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_char)
{
    std::string code = "char";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CHAR");
    EXPECT_EQ(tokens[0]->getLexeme(), "char");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_char8_t)
{
    std::string code = "char8_t";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CHAR8_T");
    EXPECT_EQ(tokens[0]->getLexeme(), "char8_t");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_char16_t)
{
    std::string code = "char16_t";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CHAR16_T");
    EXPECT_EQ(tokens[0]->getLexeme(), "char16_t");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_char32_t)
{
    std::string code = "char32_t";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CHAR32_T");
    EXPECT_EQ(tokens[0]->getLexeme(), "char32_t");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_compl)
{
    std::string code = "compl";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "COMPL");
    EXPECT_EQ(tokens[0]->getLexeme(), "compl");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_concept)
{
    std::string code = "concept";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CONCEPT");
    EXPECT_EQ(tokens[0]->getLexeme(), "concept");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_const)
{
    std::string code = "const";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CONST");
    EXPECT_EQ(tokens[0]->getLexeme(), "const");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_consteval)
{
    std::string code = "consteval";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CONSTEVAL");
    EXPECT_EQ(tokens[0]->getLexeme(), "consteval");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_constexpr)
{
    std::string code = "constexpr";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CONSTEXPR");
    EXPECT_EQ(tokens[0]->getLexeme(), "constexpr");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_constinit)
{
    std::string code = "constinit";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CONSTINIT");
    EXPECT_EQ(tokens[0]->getLexeme(), "constinit");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_const_cast)
{
    std::string code = "const_cast";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CONST_CAST");
    EXPECT_EQ(tokens[0]->getLexeme(), "const_cast");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_continue)
{
    std::string code = "continue";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CONTINUE");
    EXPECT_EQ(tokens[0]->getLexeme(), "continue");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_co_await)
{
    std::string code = "co_await";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CO_AWAIT");
    EXPECT_EQ(tokens[0]->getLexeme(), "co_await");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_co_return)
{
    std::string code = "co_return";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CO_RETURN");
    EXPECT_EQ(tokens[0]->getLexeme(), "co_return");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_co_yield)
{
    std::string code = "co_yield";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "CO_YIELD");
    EXPECT_EQ(tokens[0]->getLexeme(), "co_yield");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_decltype)
{
    std::string code = "decltype";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "DECLTYPE");
    EXPECT_EQ(tokens[0]->getLexeme(), "decltype");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_default)
{
    std::string code = "default";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "DEFAULT");
    EXPECT_EQ(tokens[0]->getLexeme(), "default");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_do)
{
    std::string code = "do";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "DO");
    EXPECT_EQ(tokens[0]->getLexeme(), "do");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_Keyword_double)
{
    std::string code = "double";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0]->getType(), "DOUBLE");
    EXPECT_EQ(tokens[0]->getLexeme(), "double");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, intMainTest)
{
    std::string code = "int main() { return 0; }";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_GT(tokens.size(), 0);  // Expect some tokens to be generated
    // Additional checks can be added here for specific tokens if needed

    EXPECT_EQ(tokens[0]->getType(), "INT");
    EXPECT_EQ(tokens[0]->getLexeme(), "int");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[1]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[1]->getLexeme(), "main");
    EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 1, Col: 5, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[2]->getType(), "LEFT_PAREN");
    EXPECT_EQ(tokens[2]->getLexeme(), "(");
    EXPECT_EQ(tokens[2]->getLineFile(), "[LineFile] Line: 1, Col: 9, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[3]->getType(), "RIGHT_PAREN");
    EXPECT_EQ(tokens[3]->getLexeme(), ")");
    EXPECT_EQ(tokens[3]->getLineFile(), "[LineFile] Line: 1, Col: 10, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[4]->getType(), "LEFT_BRACE");
    EXPECT_EQ(tokens[4]->getLexeme(), "{");
    EXPECT_EQ(tokens[4]->getLineFile(), "[LineFile] Line: 1, Col: 12, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[5]->getType(), "RETURN");
    EXPECT_EQ(tokens[5]->getLexeme(), "return");
    EXPECT_EQ(tokens[5]->getLineFile(), "[LineFile] Line: 1, Col: 14, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[6]->getType(), "NUMBER");
    EXPECT_EQ(tokens[6]->getLexeme(), "0");
    EXPECT_EQ(tokens[6]->getLineFile(), "[LineFile] Line: 1, Col: 21, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[7]->getType(), "SEMICOLON");
    EXPECT_EQ(tokens[7]->getLexeme(), ";");
    EXPECT_EQ(tokens[7]->getLineFile(), "[LineFile] Line: 1, Col: 22, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[8]->getType(), "RIGHT_BRACE");
    EXPECT_EQ(tokens[8]->getLexeme(), "}");
    EXPECT_EQ(tokens[8]->getLineFile(), "[LineFile] Line: 1, Col: 24, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, variableAssigment)
{
    std::string code = "double variableName = 3.14;";
    Scanner scanner(code);
    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);
    ASSERT_EQ(tokens.size(),
              6);  // Expect 5 tokens: type, identifier, assignment, number, semicolon
    EXPECT_EQ(tokens[0]->getType(), "DOUBLE");
    EXPECT_EQ(tokens[0]->getLexeme(), "double");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[1]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[1]->getLexeme(), "variableName");
    EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 1, Col: 8, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[2]->getType(), "EQUAL");
    EXPECT_EQ(tokens[2]->getLexeme(), "=");
    EXPECT_EQ(tokens[2]->getLineFile(), "[LineFile] Line: 1, Col: 21, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[3]->getType(), "NUMBER");
    EXPECT_EQ(tokens[3]->getLexeme(), "3.14");
    EXPECT_EQ(tokens[3]->getLineFile(), "[LineFile] Line: 1, Col: 23, End Line: 0, End Col: 0");
    EXPECT_EQ(tokens[4]->getType(), "SEMICOLON");
    EXPECT_EQ(tokens[4]->getLexeme(), ";");
    EXPECT_EQ(tokens[4]->getLineFile(), "[LineFile] Line: 1, Col: 27, End Line: 0, End Col: 0");
}

// Too much noisy
TEST_F(ScannerTest, ScanTokens_ComplexCode)
{
    std::string code =
        "int main() {\n"
        "    std::cout << \"Hello, World!\";\n"
        "    return;\n"
        "}\n";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_GT(tokens.size(), 0);  // Expect some tokens to be generated
    // Additional checks can be added here for specific tokens if needed

    // [Scanner][logTokens]Token Type: INT, Lexeme: int, LineFile: [LineFile] Line: 1, Col: 1, End
    // Line: 0, End Col: 0
    EXPECT_EQ(tokens[0]->getType(), "INT");
    EXPECT_EQ(tokens[0]->getLexeme(), "int");
    EXPECT_EQ(tokens[0]->getLineFile(), "[LineFile] Line: 1, Col: 1, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: IDENTIFIER, Lexeme: main, LineFile: [LineFile] Line: 1, Col:
    // 5, End Line: 0, End Col: 0
    EXPECT_EQ(tokens[1]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[1]->getLexeme(), "main");
    EXPECT_EQ(tokens[1]->getLineFile(), "[LineFile] Line: 1, Col: 5, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: LEFT_PAREN, Lexeme: (, LineFile: [LineFile] Line: 1, Col: 9,
    // End Line: 0, End Col: 0
    EXPECT_EQ(tokens[2]->getType(), "LEFT_PAREN");
    EXPECT_EQ(tokens[2]->getLexeme(), "(");
    EXPECT_EQ(tokens[2]->getLineFile(), "[LineFile] Line: 1, Col: 9, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: RIGHT_PAREN, Lexeme: ), LineFile: [LineFile] Line: 1, Col:
    // 10, End Line: 0, End Col: 0
    EXPECT_EQ(tokens[3]->getType(), "RIGHT_PAREN");
    EXPECT_EQ(tokens[3]->getLexeme(), ")");
    EXPECT_EQ(tokens[3]->getLineFile(), "[LineFile] Line: 1, Col: 10, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: LEFT_BRACE, Lexeme: {, LineFile: [LineFile] Line: 1, Col: 12,
    // End Line: 0, End Col: 0
    EXPECT_EQ(tokens[4]->getType(), "LEFT_BRACE");
    EXPECT_EQ(tokens[4]->getLexeme(), "{");
    EXPECT_EQ(tokens[4]->getLineFile(), "[LineFile] Line: 1, Col: 12, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: IDENTIFIER, Lexeme: std, LineFile: [LineFile] Line: 2, Col:
    // 5, End Line: 0, End Col: 0
    EXPECT_EQ(tokens[5]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[5]->getLexeme(), "std");
    EXPECT_EQ(tokens[5]->getLineFile(), "[LineFile] Line: 2, Col: 5, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: COLON, Lexeme: :, LineFile: [LineFile] Line: 2, Col: 8, End
    // Line: 0, End Col: 0
    EXPECT_EQ(tokens[6]->getType(), "COLON");
    EXPECT_EQ(tokens[6]->getLexeme(), ":");
    EXPECT_EQ(tokens[6]->getLineFile(), "[LineFile] Line: 2, Col: 8, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: COLON, Lexeme: :, LineFile: [LineFile] Line: 2, Col: 9, End
    // Line: 0, End Col: 0
    EXPECT_EQ(tokens[7]->getType(), "COLON");
    EXPECT_EQ(tokens[7]->getLexeme(), ":");
    EXPECT_EQ(tokens[7]->getLineFile(), "[LineFile] Line: 2, Col: 9, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: IDENTIFIER, Lexeme: cout, LineFile: [LineFile] Line: 2, Col:
    // 10, End Line: 0, End Col: 0
    EXPECT_EQ(tokens[8]->getType(), "IDENTIFIER");
    EXPECT_EQ(tokens[8]->getLexeme(), "cout");
    EXPECT_EQ(tokens[8]->getLineFile(), "[LineFile] Line: 2, Col: 10, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: LESS, Lexeme: <, LineFile: [LineFile] Line: 2, Col: 15, End
    // Line: 0, End Col: 0
    EXPECT_EQ(tokens[9]->getType(), "LESS");
    EXPECT_EQ(tokens[9]->getLexeme(), "<");
    EXPECT_EQ(tokens[9]->getLineFile(), "[LineFile] Line: 2, Col: 15, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: LESS, Lexeme: <, LineFile: [LineFile] Line: 2, Col: 16, End
    // Line: 0, End Col: 0
    EXPECT_EQ(tokens[10]->getType(), "LESS");
    EXPECT_EQ(tokens[10]->getLexeme(), "<");
    EXPECT_EQ(tokens[10]->getLineFile(), "[LineFile] Line: 2, Col: 16, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: STRING, Lexeme: Hello, World!, LineFile: [LineFile] Line: 2,
    // Col: 18, End Line: 0, End Col: 0
    EXPECT_EQ(tokens[11]->getType(), "STRING");
    EXPECT_EQ(tokens[11]->getLexeme(), "Hello, World!");
    EXPECT_EQ(tokens[11]->getLineFile(), "[LineFile] Line: 2, Col: 18, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: SEMICOLON, Lexeme: ;, LineFile: [LineFile] Line: 2, Col: 31,
    // End Line: 0, End Col: 0
    EXPECT_EQ(tokens[12]->getType(), "SEMICOLON");
    EXPECT_EQ(tokens[12]->getLexeme(), ";");
    EXPECT_EQ(tokens[12]->getLineFile(), "[LineFile] Line: 2, Col: 31, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: RETURN, Lexeme: return, LineFile: [LineFile] Line: 3, Col: 5,
    // End Line: 0, End Col: 0
    EXPECT_EQ(tokens[13]->getType(), "RETURN");
    EXPECT_EQ(tokens[13]->getLexeme(), "return");
    EXPECT_EQ(tokens[13]->getLineFile(), "[LineFile] Line: 3, Col: 5, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: SEMICOLON, Lexeme: ;, LineFile: [LineFile] Line: 3, Col: 11,
    // End Line: 0, End Col: 0
    EXPECT_EQ(tokens[14]->getType(), "SEMICOLON");
    EXPECT_EQ(tokens[14]->getLexeme(), ";");
    EXPECT_EQ(tokens[14]->getLineFile(), "[LineFile] Line: 3, Col: 11, End Line: 0, End Col: 0");
    // [Scanner][logTokens]Token Type: RIGHT_BRACE, Lexeme: }, LineFile: [LineFile] Line: 4, Col: 1,
    // End Line: 0, End Col: 0
    EXPECT_EQ(tokens[15]->getType(), "RIGHT_BRACE");
    EXPECT_EQ(tokens[15]->getLexeme(), "}");
    EXPECT_EQ(tokens[15]->getLineFile(), "[LineFile] Line: 4, Col: 1, End Line: 0, End Col: 0");
}

TEST_F(ScannerTest, ScanTokens_EmptyCode)
{
    std::string code = "";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 0);  // Expect no tokens for empty code
}

TEST_F(ScannerTest, ScanTokens_WhitespaceOnly)
{
    std::string code = "   \n\t  ";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_EQ(tokens.size(), 1);  // Expect no tokens for whitespace only
}

// TokenType::END_OF_FILE
TEST_F(ScannerTest, ScanTokens_EndOfFile)
{
    std::string code = "int main() {}";
    Scanner scanner(code);

    std::vector<std::shared_ptr<IToken>> tokens = scanner.scanTokens(code, m_fileName);

    ASSERT_GT(tokens.size(), 0);  // Expect some tokens to be generated
    EXPECT_EQ(tokens.back()->getType(), "END_OF_FILE");
    EXPECT_EQ(tokens.back()->getLexeme(), "");
    EXPECT_EQ(tokens.back()->getLineFile(), "[LineFile] Line: 1, Col: 14, End Line: 0, End Col: 0");
}
