#include "../../../src/ProcessSourceFiles/ContainersInterface/ContainersInterface.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"
#include "../../../src/ProcessSourceFiles/SyntaxTrees/ClassST.h"

class MockContainersInterface : public IContainersInterface
{
    // When you mock something like IContainersInterface, you are not testing the container itself —
    // you already did that with your real implementation tests. Instead, you are testing code that
    // depends on the container.
   public:
    MOCK_METHOD(void, addClass, (std::shared_ptr<ClassST> classST), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<ClassST>>, getClasses, (), (const, override));
    MOCK_METHOD(std::shared_ptr<ClassST>, getClassByName, (const std::string&), (const, override));
    MOCK_METHOD(void, clearClassesContainer, (), (override));
};

TEST(ContainersInterfaceTest, SingletonReturnsSameInstance)
{
    IContainersInterface& instance1 = ContainersInterface::getInstance();
    IContainersInterface& instance2 = ContainersInterface::getInstance();

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
        IContainersInterface& container = ContainersInterface::getInstance();
        container.clearClassesContainer();
    }
};

TEST_F(ContainerInterfaceTest, AddAndRetrieveClass)
{
    IContainersInterface& container = ContainersInterface::getInstance();

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
    IContainersInterface& container = ContainersInterface::getInstance();

    auto retrievedClass = container.getClassByName("NonExistentClass");
    EXPECT_EQ(retrievedClass, nullptr);
}

TEST_F(ContainerInterfaceTest, AddMultipleClassesAndRetrieve)
{
    IContainersInterface& container = ContainersInterface::getInstance();

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
    IContainersInterface& container = ContainersInterface::getInstance();

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
    IContainersInterface& container = ContainersInterface::getInstance();

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

TEST_F(ContainerInterfaceTest, ClearClassesContainer)
{
    IContainersInterface& container = ContainersInterface::getInstance();

    auto token = std::make_shared<Token>(TokenType::IDENTIFIER, "ClearClass", DefaultLineFile);
    auto classST = std::make_shared<ClassST>(token);
    container.addClass(classST);

    ASSERT_FALSE(container.getClasses().empty());

    container.clearClassesContainer();
    EXPECT_TRUE(container.getClasses().empty());
}

TEST_F(ContainerInterfaceTest, RetrieveClassIsCaseSensitive)
{
    IContainersInterface& container = ContainersInterface::getInstance();

    auto token = std::make_shared<Token>(TokenType::IDENTIFIER, "CaseClass", DefaultLineFile);
    auto classST = std::make_shared<ClassST>(token);
    container.addClass(classST);

    auto retrievedLower = container.getClassByName("caseclass");
    EXPECT_EQ(retrievedLower, nullptr);  // Should not match

    auto retrievedExact = container.getClassByName("CaseClass");
    EXPECT_NE(retrievedExact, nullptr);  // Should match
}

TEST_F(ContainerInterfaceTest, AddNullptrClassDoesNothing)
{
    IContainersInterface& container = ContainersInterface::getInstance();

    container.addClass(nullptr);  // Simulate accidental nullptr

    auto allClasses = container.getClasses();
    EXPECT_TRUE(std::all_of(allClasses.begin(), allClasses.end(),
                            [](auto& cls) { return cls != nullptr; }));
}

TEST_F(ContainerInterfaceTest, MultipleRetrievalConsistency)
{
    IContainersInterface& container = ContainersInterface::getInstance();

    auto token = std::make_shared<Token>(TokenType::IDENTIFIER, "RepeatClass", DefaultLineFile);
    auto classST = std::make_shared<ClassST>(token);
    container.addClass(classST);

    auto firstRetrieval = container.getClassByName("RepeatClass");
    auto secondRetrieval = container.getClassByName("RepeatClass");

    EXPECT_EQ(firstRetrieval, secondRetrieval);  // Same shared_ptr
}

TEST_F(ContainerInterfaceTest, StressTestAddManyClasses)
{
    IContainersInterface& container = ContainersInterface::getInstance();

    for (int i = 0; i < 1000; ++i)
    {
        auto name = "Class_" + std::to_string(i);
        auto token = std::make_shared<Token>(TokenType::IDENTIFIER, name, DefaultLineFile);
        auto classST = std::make_shared<ClassST>(token);
        container.addClass(classST);
    }

    EXPECT_EQ(container.getClasses().size(), 1000);
    EXPECT_NE(container.getClassByName("Class_500"), nullptr);
}

TEST_F(ContainerInterfaceTest, EmptyContainerReturnsNull)
{
    IContainersInterface& container = ContainersInterface::getInstance();

    auto retrieved = container.getClassByName("NothingHere");
    EXPECT_EQ(retrieved, nullptr);
}

// These tests don’t use the real singleton anymore. Instead, they validate how your business logic
// would interact with IContainersInterface.

TEST(MockContainersInterfaceTest, AddClassIsCalled)
{
    MockContainersInterface mock;

    auto token = std::make_shared<Token>(TokenType::IDENTIFIER, "MockClass",
                                         LineFile{1, 2, 3, 4, "MockFile.cpp"});
    auto classST = std::make_shared<ClassST>(token);

    EXPECT_CALL(mock, addClass(classST)).Times(1);

    // Act
    mock.addClass(classST);
}

TEST(MockContainersInterfaceTest, GetClassByNameReturnsStub)
{
    MockContainersInterface mock;

    auto token = std::make_shared<Token>(TokenType::IDENTIFIER, "StubClass",
                                         LineFile{1, 2, 3, 4, "StubFile.cpp"});
    auto expectedClass = std::make_shared<ClassST>(token);

    // I create the method call that i expect and than... it returns the value. This is the first
    // level, how about second?
    EXPECT_CALL(mock, getClassByName("StubClass")).WillOnce(testing::Return(expectedClass));

    auto result = mock.getClassByName("StubClass");

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getClassName(), "StubClass");
}

TEST(MockContainersInterfaceTest, GetClassesReturnsEmpty)
{
    MockContainersInterface mock;

    EXPECT_CALL(mock, getClasses())
        .WillOnce(testing::Return(std::vector<std::shared_ptr<ClassST>>{}));

    auto classes = mock.getClasses();
    EXPECT_TRUE(classes.empty());
}
