#include "../../src/ProcessSourceFiles/FolderGraph.h"
// #include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

class FolderGraphTest : public ::testing::Test
{
   protected:
    const std::shared_ptr<ItemInFolder> root =
        instantiateChid("root", "pathStr", "sizeStr", "urlStr", "html_urlStr", "git_urlStr",
                        "download_urlStr", "typeStr");

    const std::shared_ptr<ItemInFolder> child1 =
        instantiateChid("child1", "pathStr", "sizeStr", "urlStr", "html_urlStr", "git_urlStr",
                        "download_urlStr", "typeStr");
    const std::shared_ptr<ItemInFolder> child2 =
        instantiateChid("child2", "pathStr", "sizeStr", "urlStr", "html_urlStr", "git_urlStr",
                        "download_urlStr", "typeStr");

    std::shared_ptr<ItemInFolder> instantiateChid(const std::string& name, const std::string& path,
                                                  const std::string& size, const std::string& url,
                                                  const std::string& html_url,
                                                  const std::string& git_url,
                                                  const std::string& download_url,
                                                  const std::string& type)
    {
        return std::make_shared<ItemInFolder>(name, path, size, url, html_url, git_url,
                                              download_url, type);
    }
};

TEST_F(FolderGraphTest, testCreateGraphWithRootNode)
{
    FolderGraph graph(root);

    EXPECT_EQ(graph.getRoot()->getName(), "root");
    EXPECT_TRUE(graph.getRoot()->getChildren().empty());
}

TEST_F(FolderGraphTest, testCreateGraphWithRootNodeAndAddOneChild)
{
    FolderGraph graph(root);

    EXPECT_EQ(graph.getRoot()->getName(), "root");
    EXPECT_TRUE(graph.getRoot()->getChildren().empty());

    graph.addEdge(graph.getRoot(), child1);

    EXPECT_EQ(graph.getRoot()->getChildren().size(), 1);
    EXPECT_EQ(graph.getRoot()->getChildren()[0]->getName(), "child1");
}

TEST_F(FolderGraphTest, testCreateGraphWithRootNodeAndAddChieldPassingTwochildren)
{
    FolderGraph graph(root);

    EXPECT_EQ(graph.getRoot()->getName(), "root");
    EXPECT_TRUE(graph.getRoot()->getChildren().empty());

    graph.addEdge(graph.getRoot(), child1);
    graph.addEdge(graph.getRoot(), child2);

    EXPECT_EQ(graph.getRoot()->getChildren().size(), 2);
    EXPECT_EQ(graph.getRoot()->getChildren()[0]->getName(), "child1");
    EXPECT_EQ(graph.getRoot()->getChildren()[1]->getName(), "child2");
}

// Add a node	Verify that adding a node works and node count increases.
// Add an edge	Ensure edge creation works between two nodes.
// Add duplicate nodes	Check if duplicate nodes are handled (ignored, replaced, or error).
// Add duplicate edges	Check if multiple edges between same nodes behave correctly (allowed or
// prevented). Remove node	Deleting a node also removes its edges. Remove edge	Only edge is
// deleted, nodes remain. Search for node/edge	Find if a node or edge exists. Traversal tests
// (optional)	Depth-First Search (DFS), Breadth-First Search (BFS) visit expected nodes in order.
// Detect cycles (if directed graph)	Validate if cycle detection works (important for dependency
// graphs).