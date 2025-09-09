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

TEST_F(ClassGraphTest, DuplicateEdgePrevention)
{
    g.addClassWithBases("A", {"B"});
    g.addClassWithBases("A", {"B"});
    EXPECT_EQ(g.edgeCount(), 1u);
    EXPECT_EQ(g.basesOf("A"), std::vector<std::string>{"B"});
    EXPECT_EQ(g.derivedOf("B"), std::vector<std::string>{"A"});
}

TEST_F(ClassGraphTest, ClearAndReuse)
{
    g.addClassWithBases("A", {"B"});
    g.clear();
    EXPECT_EQ(g.nodeCount(), 0u);
    EXPECT_EQ(g.edgeCount(), 0u);
    g.addClassWithBases("C", {"D"});
    EXPECT_EQ(g.nodeCount(), 2u);
    EXPECT_EQ(g.edgeCount(), 1u);
}

TEST_F(ClassGraphTest, AncestorTraversalWithMultipleLevels)
{
    g.addClassWithBases("A", {"B"});
    g.addClassWithBases("B", {"C"});
    g.addClassWithBases("C", {"D"});
    auto ancestors = g.allAncestors("A");
    EXPECT_EQ(ancestors, (std::vector<std::string>{"B", "C", "D"}));
}

TEST_F(ClassGraphTest, DOTandJSONOutputConsistency)
{
    g.addClassWithBases("X", {"Y", "Z"});
    auto dot = g.toDot("Graph");
    EXPECT_NE(dot.find("\"X\" -> \"Y\""), std::string::npos);
    EXPECT_NE(dot.find("\"X\" -> \"Z\""), std::string::npos);

    auto json = g.toJsonAsString();
    EXPECT_NE(json.find("\"X\""), std::string::npos);
    EXPECT_NE(json.find("\"Y\""), std::string::npos);
    EXPECT_NE(json.find("\"Z\""), std::string::npos);
}

TEST_F(ClassGraphTest, AddClassWithEmptyName)
{
    g.addClassWithBases("", {"Base"});
    EXPECT_EQ(g.nodeCount(), 0u);
    EXPECT_EQ(g.edgeCount(), 0u);
    EXPECT_FALSE(g.hasNode(""));

    g.addClassWithBases("Derived", {""});
    EXPECT_EQ(g.nodeCount(), 1u);
    EXPECT_EQ(g.edgeCount(), 0u);
    EXPECT_TRUE(g.hasNode("Derived"));
    EXPECT_FALSE(g.hasNode(""));

    EXPECT_TRUE(g.basesOf("Derived").empty());
    EXPECT_TRUE(g.derivedOf("").empty());
}

TEST_F(ClassGraphTest, AncestorsOfNonExistentClass)
{
    g.addClassWithBases("A", {"B"});
    auto ancestors = g.allAncestors("NonExistent");
    EXPECT_TRUE(ancestors.empty());
}

TEST_F(ClassGraphTest, NodesAndEdgesAfterMultipleAdditions)
{
    g.addClassWithBases("A", {"B"});
    g.addClassWithBases("C", {"D", "E"});
    g.addClassWithBases("F", {});
    EXPECT_EQ(g.nodeCount(), 6u);  // A, B, C, D, E, F
    EXPECT_EQ(g.edgeCount(), 3u);  // A->B, C->D, C->E
}

TEST_F(ClassGraphTest, ToJsonAsStringFormatCheck)
{
    g.addClassWithBases("M", {"N"});
    auto json = g.toJsonAsString();
    EXPECT_NE(json.find("\"M\""), std::string::npos);
    EXPECT_NE(json.find("\"N\""), std::string::npos);
    EXPECT_NE(json.find("["), std::string::npos);
    EXPECT_NE(json.find("]"), std::string::npos);
}

TEST_F(ClassGraphTest, AddClassWithBases_EmptyBaseNames)
{
    g.addClassWithBases("A", {});
    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_EQ(g.nodeCount(), 1u);
    EXPECT_EQ(g.edgeCount(), 0u);
    EXPECT_TRUE(g.basesOf("A").empty());
    EXPECT_TRUE(g.derivedOf("A").empty());
}

TEST_F(ClassGraphTest, AddClassWithBases_EmptyClassName)
{
    g.addClassWithBases("", {"B", "C"});
    EXPECT_FALSE(g.hasNode(""));
    EXPECT_EQ(g.nodeCount(), 0u);
    EXPECT_EQ(g.edgeCount(), 0u);
}

TEST_F(ClassGraphTest, AddClassWithBases_EmptyClassAndBaseNames)
{
    g.addClassWithBases("", {});
    EXPECT_FALSE(g.hasNode(""));
    EXPECT_EQ(g.nodeCount(), 0u);
    EXPECT_EQ(g.edgeCount(), 0u);
}

TEST_F(ClassGraphTest, AddClassWithBases_BaseNamesWithEmptyStrings)
{
    g.addClassWithBases("A", {"", "B", ""});
    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_TRUE(g.hasNode("B"));
    EXPECT_FALSE(g.hasNode(""));
    EXPECT_EQ(g.nodeCount(), 2u);  // A and B
    EXPECT_EQ(g.edgeCount(), 1u);  // A->B
    EXPECT_EQ(g.basesOf("A"), (std::vector<std::string>{"B"}));
    EXPECT_EQ(g.derivedOf("B"), (std::vector<std::string>{"A"}));
}

TEST_F(ClassGraphTest, AddClassWithBases_DuplicateBaseNames)
{
    g.addClassWithBases("A", {"B", "B", "C", "C"});
    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_TRUE(g.hasNode("B"));
    EXPECT_TRUE(g.hasNode("C"));
    EXPECT_EQ(g.nodeCount(), 3u);  // A, B, C
    EXPECT_EQ(g.edgeCount(), 2u);  // A->B, A->C
    EXPECT_EQ(g.basesOf("A"), (std::vector<std::string>{"B", "C"}));
    EXPECT_EQ(g.derivedOf("B"), (std::vector<std::string>{"A"}));
    EXPECT_EQ(g.derivedOf("C"), (std::vector<std::string>{"A"}));
}

TEST_F(ClassGraphTest, AddClassWithBases_SelfInheritance)  // Not a valid operation
{
    g.addClassWithBases("A", {"A"});
    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_EQ(g.nodeCount(), 1u);
    EXPECT_EQ(g.edgeCount(), 0u);
}

TEST_F(ClassGraphTest, AddClassWithBases_MultipleClassesAndBases)
{
    g.addClassWithBases("A", {"B", "C"});
    g.addClassWithBases("D", {"E", "F"});
    g.addClassWithBases("G", {"A"});
    g.addClassWithBases("H", {"I", "D", "C"});

    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_TRUE(g.hasNode("B"));
    EXPECT_TRUE(g.hasNode("C"));
    EXPECT_TRUE(g.hasNode("D"));
    EXPECT_TRUE(g.hasNode("E"));
    EXPECT_TRUE(g.hasNode("F"));
    EXPECT_TRUE(g.hasNode("G"));
    EXPECT_TRUE(g.hasNode("H"));
    EXPECT_TRUE(g.hasNode("I"));

    EXPECT_EQ(g.nodeCount(), 9u);
    EXPECT_EQ(g.edgeCount(), 8u);

    // Direct bases
    EXPECT_EQ(g.basesOf("A"), (std::vector<std::string>{"B", "C"}));
    EXPECT_EQ(g.basesOf("D"), (std::vector<std::string>{"E", "F"}));
    EXPECT_EQ(g.basesOf("G"), (std::vector<std::string>{"A"}));
    EXPECT_EQ(g.basesOf("H"), (std::vector<std::string>{"C", "D", "I"}));  // sorted

    // Reverse: who derives from each
    EXPECT_EQ(g.derivedOf("A"), (std::vector<std::string>{"G"}));
    EXPECT_EQ(g.derivedOf("B"), (std::vector<std::string>{"A"}));
    EXPECT_EQ(g.derivedOf("C"), (std::vector<std::string>{"A", "H"}));  // sorted
    EXPECT_EQ(g.derivedOf("D"), (std::vector<std::string>{"H"}));
    EXPECT_EQ(g.derivedOf("E"), (std::vector<std::string>{"D"}));
    EXPECT_EQ(g.derivedOf("F"), (std::vector<std::string>{"D"}));
    EXPECT_EQ(g.derivedOf("I"), (std::vector<std::string>{"H"}));

    // Ancestors of H: {i, d, c, e, f}
    auto ancestorsH = g.allAncestors("H");
    EXPECT_EQ(ancestorsH, (std::vector<std::string>{"C", "D", "E", "F", "I"}));
    std::sort(ancestorsH.begin(), ancestorsH.end());
    EXPECT_EQ(ancestorsH, (std::vector<std::string>{"C", "D", "E", "F", "I"}));
}

TEST_F(ClassGraphTest, ToJsonFormatCheck)
{
    g.addClassWithBases("M", {"N"});

    EXPECT_TRUE(g.hasNode("M"));
    EXPECT_TRUE(g.hasNode("N"));
    EXPECT_EQ(g.nodeCount(), 2u);
    EXPECT_EQ(g.edgeCount(), 1u);

    auto json = g.toJson();
    auto jsonStr = g.toJson().dump();  // convert to string

    EXPECT_NE(jsonStr.find("\"M\""), std::string::npos);
    EXPECT_NE(jsonStr.find("\"N\""), std::string::npos);
    EXPECT_NE(jsonStr.find("["), std::string::npos);
    EXPECT_NE(jsonStr.find("]"), std::string::npos);
}

// Example:
// {
//   "A": ["B", "C"],
//   "B": [],
//   "C": ["D"]
// }
TEST_F(ClassGraphTest, ToJsonContentCheck)
{
    g.addClassWithBases("A", {"B", "C"});
    g.addClassWithBases("C", {"D"});

    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_TRUE(g.hasNode("B"));
    EXPECT_TRUE(g.hasNode("C"));
    EXPECT_TRUE(g.hasNode("D"));
    EXPECT_EQ(g.nodeCount(), 4u);
    EXPECT_EQ(g.edgeCount(), 3u);

    auto json = g.toJson().dump();

    EXPECT_NE(json.find("\"A\""), std::string::npos);
    EXPECT_NE(json.find("\"B\""), std::string::npos);
    EXPECT_NE(json.find("\"C\""), std::string::npos);
    EXPECT_NE(json.find("\"D\""), std::string::npos);

    // Check specific relationships
    EXPECT_NE(json.find("\"A\":[\"B\",\"C\"]"), std::string::npos);
    EXPECT_NE(json.find("\"B\":[]"), std::string::npos);
    EXPECT_NE(json.find("\"C\":[\"D\"]"), std::string::npos);
    EXPECT_NE(json.find("\"D\":[]"), std::string::npos);
}

// export to dot file
TEST_F(ClassGraphTest, ExportToDotFile)
{
    g.addClassWithBases("A", {"B", "C"});
    g.addClassWithBases("C", {"D"});

    EXPECT_TRUE(g.hasNode("A"));
    EXPECT_TRUE(g.hasNode("B"));
    EXPECT_TRUE(g.hasNode("C"));
    EXPECT_TRUE(g.hasNode("D"));
    EXPECT_EQ(g.nodeCount(), 4u);
    EXPECT_EQ(g.edgeCount(), 3u);

    // Export to DOT file
    EXPECT_NO_THROW(g.toDot("test_graph", true));

    std::remove("test_graph.dot");
}
