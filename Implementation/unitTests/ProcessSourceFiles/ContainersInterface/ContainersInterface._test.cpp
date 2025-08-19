#include "../../../src/ProcessSourceFiles/ContainersInterface/ContainersInterface.h"

#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"
#include "../../../src/ProcessSourceFiles/SyntaxTrees/ClassST.h"

TEST(ContainersInterfaceTest, SingletonReturnsSameInstance)
{
    ContainersInterface& instance1 = ContainersInterface::getInstance();
    ContainersInterface& instance2 = ContainersInterface::getInstance();

    // Check that both references point to the same object
    EXPECT_EQ(&instance1, &instance2);
}

class ContainerInterfaceTest : public ::testing::Test
{
   protected:
    LineFile DefaultLineFile{1, 2, 3, 4, "File1.cpp"};
    LineFile DefaultLineFile2{1, 2, 3, 4, "File1.cpp"};

   protected:
    void SetUp() override {}

    void TearDown() override
    {
        ContainersInterface& container = ContainersInterface::getInstance();
        container.clearClassesContainer();
    }
};

TEST_F(ContainerInterfaceTest, AddAndRetrieveClass)
{
    ContainersInterface& container = ContainersInterface::getInstance();

    auto className = "TestClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    auto classST = std::make_shared<ClassST>(token);

    container.addClass(classST);

    auto retrievedClass = container.getClassByName(className);
    ASSERT_NE(retrievedClass, nullptr);
}

TEST_F(ContainerInterfaceTest, RetrieveNonExistentClass)
{
    ContainersInterface& container = ContainersInterface::getInstance();

    auto retrievedClass = container.getClassByName("NonExistentClass");
    EXPECT_EQ(retrievedClass, nullptr);
}

TEST_F(ContainerInterfaceTest, AddMultipleClassesAndRetrieve)
{
    ContainersInterface& container = ContainersInterface::getInstance();

    auto className1 = "FirstClass";
    std::shared_ptr<IToken> token1 =
        std::make_shared<Token>(TokenType::IDENTIFIER, className1, DefaultLineFile);
    auto classST1 = std::make_shared<ClassST>(token1);

    auto className2 = "SecondClass";
    std::shared_ptr<IToken> token2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, className2, DefaultLineFile);
    auto classST2 = std::make_shared<ClassST>(token2);

    container.addClass(classST1);
    container.addClass(classST2);

    auto retrievedClass1 = container.getClassByName(className1);
    ASSERT_NE(retrievedClass1, nullptr);
    EXPECT_EQ(retrievedClass1->getClassName(), className1);

    auto retrievedClass2 = container.getClassByName(className2);
    ASSERT_NE(retrievedClass2, nullptr);
    EXPECT_EQ(retrievedClass2->getClassName(), className2);
}

TEST_F(ContainerInterfaceTest, RetreveAllClasses)
{
    ContainersInterface& container = ContainersInterface::getInstance();

    auto className1 = "AlphaClass";
    std::shared_ptr<IToken> token1 =
        std::make_shared<Token>(TokenType::IDENTIFIER, className1, DefaultLineFile);
    auto classST1 = std::make_shared<ClassST>(token1);

    auto className2 = "BetaClass";
    std::shared_ptr<IToken> token2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, className2, DefaultLineFile);
    auto classST2 = std::make_shared<ClassST>(token2);

    container.addClass(classST1);
    container.addClass(classST2);

    auto allClasses = container.getClasses();
    EXPECT_GE(allClasses.size(), 2);  // At least the two we just added

    bool foundAlpha = false;
    bool foundBeta = false;
    for (const auto& cls : allClasses)
    {
        if (cls->getClassName() == className1)
        {
            foundAlpha = true;
        }
        else if (cls->getClassName() == className2)
        {
            foundBeta = true;
        }
    }

    EXPECT_TRUE(foundAlpha);
    EXPECT_TRUE(foundBeta);
}

// TODO -> This is allowed, i'll going to save the fale path in the LineFile class!!!!!!!!!!!!!!!!!

TEST_F(ContainerInterfaceTest, AddDuplicateClassThrows)
{
    ContainersInterface& container = ContainersInterface::getInstance();

    auto className = "DuplicateClass";
    std::shared_ptr<IToken> token1 =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    std::shared_ptr<IToken> token2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile2);
    auto classST1 = std::make_shared<ClassST>(token1);
    auto classST2 = std::make_shared<ClassST>(token2);

    container.addClass(classST1);
    container.addClass(classST2);

    auto classes = container.getClasses();
    std::vector<std::shared_ptr<ClassST>> expectedClasses = {classST1, classST2};

    EXPECT_EQ(classes.size(), 2);
    for (size_t i = 0; i < classes.size(); ++i)
    {
        EXPECT_EQ(classes[i]->getClassName(), expectedClasses[i]->getClassName());
    }
}
