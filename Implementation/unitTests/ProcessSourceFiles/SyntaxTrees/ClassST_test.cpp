#include "../../../src/ProcessSourceFiles/SyntaxTrees/ClassST.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"

class ClassSTTest : public ::testing::Test
{
   protected:
    LineFile DefaultLineFile{1, 2, 3, 4};

   protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ClassSTTest, SimpleClassStConstructor)
{
    auto className = "SimpleClass";
    ClassST simpleClass(className);

    EXPECT_EQ(simpleClass.getClassName(), className);
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingToken)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingEmptyToken)
{
    std::string className;
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);

    EXPECT_THROW(ClassST simpleClass(token), std::runtime_error);
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingInvalidToken)
{
    std::string className;
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::BANG, className, DefaultLineFile);

    EXPECT_THROW(ClassST simpleClass(token), std::runtime_error);
}
