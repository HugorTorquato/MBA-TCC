#include "../../../src/ProcessSourceFiles/SyntaxTrees/ClassST.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

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
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingToken)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());
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

TEST_F(ClassSTTest, SimpleClassWith_UniqueInherency)
{
    auto className = "SimpleClass";
    auto baseClassName = "SimpleBaseClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());

    std::shared_ptr<IToken> accessBaseClass =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName, DefaultLineFile);

    simpleClass.addInherencyToClassObject(accessBaseClass, tokenBaseClass);
    auto baseClassArray = simpleClass.getInherencyArray();
    EXPECT_FALSE(baseClassArray.empty());
    EXPECT_EQ(baseClassArray.size(), 1);
    EXPECT_EQ(baseClassArray.front().first->getLexeme(), "public");
    EXPECT_EQ(baseClassArray.front().second->getLexeme(), baseClassName);
}

TEST_F(ClassSTTest, SimpleClassWith_MultipleInherencies)
{
    auto className = "SimpleClass";
    auto baseClassName = "SimpleBaseClass";
    auto baseClassName2 = "SimpleBaseClass2";

    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());

    std::shared_ptr<IToken> accessBaseClass =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName, DefaultLineFile);
    std::shared_ptr<IToken> accessBaseClass2 =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName2, DefaultLineFile);

    simpleClass.addInherencyToClassObject(accessBaseClass, tokenBaseClass);
    simpleClass.addInherencyToClassObject(accessBaseClass2, tokenBaseClass2);

    auto baseClassArray = simpleClass.getInherencyArray();
    std::vector<std::string> expectedNames = {baseClassName, baseClassName2};

    EXPECT_FALSE(baseClassArray.empty());
    EXPECT_EQ(baseClassArray.size(), 2);

    for (size_t i = 0; i < baseClassArray.size(); ++i)
    {
        EXPECT_EQ(baseClassArray[i].first->getTypeEnum(), TokenType::PUBLIC);
        EXPECT_EQ(baseClassArray[i].second->getTypeEnum(), TokenType::IDENTIFIER);
        EXPECT_EQ(baseClassArray[i].second->getLexeme(), expectedNames[i]);
    }
}

TEST_F(ClassSTTest, ClassST_AddInherency_InvalidAccessType)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> invalidAccessType =
        std::make_shared<Token>(TokenType::BANG, "invalid", DefaultLineFile);
    std::shared_ptr<IToken> baseClassToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "BaseClass", DefaultLineFile);

    EXPECT_THROW(simpleClass.addInherencyToClassObject(invalidAccessType, baseClassToken),
                 std::runtime_error);
}

TEST_F(ClassSTTest, ClassST_AddInherency_InvalidClassName)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> accessType =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> invalidClassToken =
        std::make_shared<Token>(TokenType::BANG, "invalid", DefaultLineFile);

    EXPECT_THROW(simpleClass.addInherencyToClassObject(accessType, invalidClassToken),
                 std::runtime_error);
}

TEST_F(ClassSTTest, ClassST_AddInherency_ValidAccessTypeAndClassName)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> accessType =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> classToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "BaseClass", DefaultLineFile);

    EXPECT_NO_THROW(simpleClass.addInherencyToClassObject(accessType, classToken));
}
