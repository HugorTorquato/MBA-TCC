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
    LineFile DefaultLineFile{1, 2, 3, 4};

   protected:
    void SetUp() override {}

    void TearDown() override {}
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

// TODO -> This is allowed, i'll going to save the fale path in the LineFile class!!!!!!!!!!!!!!!!!

// TEST_F(ContainerInterfaceTest, AddDuplicateClassThrows)
// {
//     ContainersInterface& container = ContainersInterface::getInstance();

//     auto className = "DuplicateClass";
//     std::shared_ptr<IToken> token =
//         std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
//     auto classST1 = std::make_shared<ClassST>(token);
//     auto classST2 = std::make_shared<ClassST>(token);

//     container.addClass(classST1);

//    // Attempt to add the duplicate class and expect an exception
//    EXPECT_THROW(container.addClass(classST2), std::runtime_error);
// }
