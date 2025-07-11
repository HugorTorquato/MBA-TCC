#include "../../../src/ProcessSourceFiles/Scanner/Scanner.h"

#include <gtest/gtest.h>

class ScannerTest : public ::testing::Test
{

    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ScannerTest, ScanTokens_EmptyInput) {
    Scanner scanner;
    std::string code = "";
    std::vector<std::string> tokens = scanner.scanTokens(code);

    ASSERT_TRUE(tokens.empty());
}


// TEST_F(ScannerTest, ScanTokens_EmptyInput) {
//     Scanner scanner;
//     std::string code = "int main() { return 0; }";
//     std::vector<std::string> tokens = scanner.scanTokens(code);

//     ASSERT_TRUE(tokens.empty());
//     // ASSERT_FALSE(tokens.empty());
//     // EXPECT_EQ(tokens[0], "int");
//     // EXPECT_EQ(tokens[1], "main");
//     // EXPECT_EQ(tokens[2], "return");
//     // EXPECT_EQ(tokens[3], "0");
// }