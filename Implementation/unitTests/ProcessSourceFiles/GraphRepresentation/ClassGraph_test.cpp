#include "../../../src/ProcessSourceFiles/GraphRepresentation/ClassGraph.h"

#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"

class ClassGraphTest : public ::testing::Test
{
   protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ClassGraphTest, exerciseBuildGraph)
{
    ClassGraph graph;
    std::vector<std::shared_ptr<ClassST>> classes;
    EXPECT_NO_THROW(graph.buildGraph(classes));
}

TEST_F(ClassGraphTest, BuildGraph_WithClasses)
{
    ClassGraph graph;

    auto classToken1 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "ClassA", LineFile(1, 1, 0, 0));
    auto classST1 = std::make_shared<ClassST>(classToken1);

    auto classToken2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "ClassB", LineFile(2, 1, 0, 0));
    auto classST2 = std::make_shared<ClassST>(classToken2);

    // ClassB inherits from ClassA
    auto accessType = std::make_shared<Token>(TokenType::PUBLIC, "public", LineFile(2, 7, 0, 0));
    classST2->addInherencyToClassObject(accessType, classToken1);

    std::vector<std::shared_ptr<ClassST>> classes = {classST1, classST2};

    EXPECT_NO_THROW(graph.buildGraph(classes));

    const auto allClasses = graph.getAllClasses();
    EXPECT_EQ(allClasses.size(), 2);
    for (const auto& cls : allClasses)
    {
        EXPECT_TRUE(cls == classST1 || cls == classST2);
    }
}

TEST_F(ClassGraphTest, BuildGraph_WithNullClass)
{
    ClassGraph graph;

    std::vector<std::shared_ptr<ClassST>> classes = {nullptr};

    EXPECT_NO_THROW(graph.buildGraph(classes));

    const auto allClasses = graph.getAllClasses();
    EXPECT_TRUE(allClasses.empty());
}

TEST_F(ClassGraphTest, ClearGraph_AfterBuilding)
{
    ClassGraph graph;

    auto classToken1 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "ClassA", LineFile(1, 1, 0, 0));
    auto classST1 = std::make_shared<ClassST>(classToken1);

    auto classToken2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "ClassB", LineFile(2, 1, 0, 0));
    auto classST2 = std::make_shared<ClassST>(classToken2);

    // ClassB inherits from ClassA
    auto accessType = std::make_shared<Token>(TokenType::PUBLIC, "public", LineFile(2, 7, 0, 0));
    classST2->addInherencyToClassObject(accessType, classToken1);

    std::vector<std::shared_ptr<ClassST>> classes = {classST1, classST2};

    EXPECT_NO_THROW(graph.buildGraph(classes));

    auto allClasses = graph.getAllClasses();
    EXPECT_EQ(allClasses.size(), 2);

    // Now clear the graph
    graph.clear();

    allClasses = graph.getAllClasses();
    EXPECT_TRUE(allClasses.empty());
}
