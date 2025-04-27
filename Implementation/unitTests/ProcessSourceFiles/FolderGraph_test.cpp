#include "../../src/ProcessSourceFiles/FolderGraph.h"
// #include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

class FolderGraphTest : public ::testing::Test
{
   protected:
};

TEST_F(FolderGraphTest, testEmptyGraph)
{
    // Create an empty FolderGraph
    FolderGraph graph("empty");

    // Check if the root node is created correctly
    EXPECT_EQ(graph.getRoot()->name, "empty");
    EXPECT_TRUE(graph.getRoot()->children.empty());
}

TEST_F(FolderGraphTest, testCreateGraphWithRootNode)
{
    // Create a FolderGraph object with a root name
    FolderGraph graph("root");

    // Check if the root node is created correctly
    EXPECT_EQ(graph.getRoot()->name, "root");
    EXPECT_TRUE(graph.getRoot()->children.empty());
}

TEST_F(FolderGraphTest, testCreateGraphWithRootNodeAndAddChield)
{
    FolderGraph graph("root");

    EXPECT_EQ(graph.getRoot()->name, "root");
    EXPECT_TRUE(graph.getRoot()->children.empty());

    // Add a child to the root node
    graph.addEdge(graph.getRoot(), "child");

    // Check if the child node is added correctly
    EXPECT_EQ(graph.getRoot()->children.size(), 1);
    EXPECT_EQ(graph.getRoot()->children[0]->name, "child");
}

// Create an empty graph	Ensure graph initializes correctly with no nodes.
// Add a node	Verify that adding a node works and node count increases.
// Add an edge	Ensure edge creation works between two nodes.
// Add duplicate nodes	Check if duplicate nodes are handled (ignored, replaced, or error).
// Add duplicate edges	Check if multiple edges between same nodes behave correctly (allowed or
// prevented). Remove node	Deleting a node also removes its edges. Remove edge	Only edge is
// deleted, nodes remain. Search for node/edge	Find if a node or edge exists. Traversal tests
// (optional)	Depth-First Search (DFS), Breadth-First Search (BFS) visit expected nodes in order.
// Detect cycles (if directed graph)	Validate if cycle detection works (important for dependency
// graphs).