#include "../../../src/ProcessSourceFiles/GraphRepresentation/ClassGraph.h"

#include <gtest/gtest.h>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"

class ClassGraphTest : public ::testing::Test
{
   public:
    ClassGraph g;

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
        EXPECT_TRUE(cls == classST1->getClassName() || cls == classST2->getClassName());
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

TEST_F(ClassGraphTest, InitiallyEmpty)
{
    EXPECT_EQ(g.nodeCount(), 0u);
    EXPECT_EQ(g.edgeCount(), 0u);
    EXPECT_FALSE(g.hasNode("a"));
}

TEST_F(ClassGraphTest, AddClassWithoutBasesCreatesNodeOnly)
{
    g.addClassWithBases("A", {});
    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_EQ(g.nodeCount(), 1u);
    EXPECT_EQ(g.edgeCount(), 0u);

    EXPECT_TRUE(g.basesOf("A").empty());
    EXPECT_TRUE(g.derivedOf("A").empty());
}

TEST_F(ClassGraphTest, AddClassWithBasesUpdatesAdjacencyAndReverse)
{
    g.addClassWithBases("a", {"b", "c"});  // a : b c

    EXPECT_TRUE(g.hasNode("a"));
    EXPECT_TRUE(g.hasNode("b"));
    EXPECT_TRUE(g.hasNode("c"));

    // parents (bases) of a
    EXPECT_EQ(g.basesOf("a"), (std::vector<std::string>{"b", "c"}));

    // children (derived) of b and c
    EXPECT_EQ(g.derivedOf("b"), (std::vector<std::string>{"a"}));
    EXPECT_EQ(g.derivedOf("c"), (std::vector<std::string>{"a"}));

    EXPECT_EQ(g.edgeCount(), 2u);
}

TEST_F(ClassGraphTest, ComplexExampleMatchesYourSpec)
{
    // a: b c
    g.addClassWithBases("a", {"b", "c"});
    // d: e f
    g.addClassWithBases("d", {"e", "f"});
    // g: a
    g.addClassWithBases("g", {"a"});
    // h: i d c
    g.addClassWithBases("h", {"i", "d", "c"});

    // Direct bases
    EXPECT_EQ(g.basesOf("a"), (std::vector<std::string>{"b", "c"}));
    EXPECT_EQ(g.basesOf("d"), (std::vector<std::string>{"e", "f"}));
    EXPECT_EQ(g.basesOf("g"), (std::vector<std::string>{"a"}));
    EXPECT_EQ(g.basesOf("h"), (std::vector<std::string>{"c", "d", "i"}));  // sorted

    // Reverse: who derives from each
    EXPECT_EQ(g.derivedOf("a"), (std::vector<std::string>{"g"}));
    EXPECT_EQ(g.derivedOf("b"), (std::vector<std::string>{"a"}));
    EXPECT_EQ(g.derivedOf("c"), (std::vector<std::string>{"a", "h"}));  // sorted
    EXPECT_EQ(g.derivedOf("d"), (std::vector<std::string>{"h"}));
    EXPECT_EQ(g.derivedOf("e"), (std::vector<std::string>{"d"}));
    EXPECT_EQ(g.derivedOf("f"), (std::vector<std::string>{"d"}));
    EXPECT_EQ(g.derivedOf("i"), (std::vector<std::string>{"h"}));

    // Ancestors of h: {i, d, c, e, f}
    auto ancestorsH = g.allAncestors("h");
    EXPECT_EQ(ancestorsH, (std::vector<std::string>{"c", "d", "e", "f", "i"}));

    // Ancestors of g: {a, b, c}
    auto ancestorsG = g.allAncestors("g");
    EXPECT_EQ(ancestorsG, (std::vector<std::string>{"a", "b", "c"}));
}

TEST_F(ClassGraphTest, ToDotContainsEdges)
{
    g.addClassWithBases("a", {"b", "c"});
    g.addClassWithBases("g", {"a"});

    auto dot = g.toDot("TestGraph");
    // very light checks; avoid brittle string tests
    EXPECT_NE(dot.find("\"a\" -> \"b\""), std::string::npos);
    EXPECT_NE(dot.find("\"a\" -> \"c\""), std::string::npos);
    EXPECT_NE(dot.find("\"g\" -> \"a\""), std::string::npos);
}
