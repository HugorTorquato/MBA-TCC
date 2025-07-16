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
