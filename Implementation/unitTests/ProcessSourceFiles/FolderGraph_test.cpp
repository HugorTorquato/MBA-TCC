#include "../../src/ProcessSourceFiles/FolderGraph.h"
// #include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

class FolderGraphTest : public ::testing::Test
{
   protected:
    const std::shared_ptr<ItemInFolder> root = instantiateChid(
        "root", "pathStr", 0, "urlStr", "html_urlStr", "git_urlStr", "download_urlStr", "typeStr");

    const std::shared_ptr<ItemInFolder> child1 =
        instantiateChid("child1", "pathStr", 0, "urlStr", "html_urlStr", "git_urlStr",
                        "download_urlStr", "typeStr");
    const std::shared_ptr<ItemInFolder> child2 =
        instantiateChid("child2", "pathStr", 0, "urlStr", "html_urlStr", "git_urlStr",
                        "download_urlStr", "typeStr");
    const std::shared_ptr<ItemInFolder> child3 =
        instantiateChid("child3", "pathStr", 0, "urlStr", "html_urlStr", "git_urlStr",
                        "download_urlStr", "typeStr");
    const std::shared_ptr<ItemInFolder> child4 =
        instantiateChid("child4", "pathStr", 0, "urlStr", "html_urlStr", "git_urlStr",
                        "download_urlStr", "typeStr");

    std::shared_ptr<ItemInFolder> instantiateChid(const std::string& name, const std::string& path,
                                                  const unsigned int size, const std::string& url,
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

TEST_F(FolderGraphTest, setAndRetreveNewRootInfo)
{
    FolderGraph graph(root);

    graph.getRoot()->setName("Newroot");
    graph.getRoot()->setPath("NewpathStr");
    graph.getRoot()->setSize(1);
    graph.getRoot()->setUrl("NewurlStr");
    graph.getRoot()->setHtmlUrl("Newhtml_urlStr");
    graph.getRoot()->setGitUrl("Newgit_urlStr");
    graph.getRoot()->setDownloadUrl("Newdownload_urlStr");
    graph.getRoot()->setType("NewtypeStr");

    EXPECT_EQ(graph.getRoot()->getName(), "Newroot");
    EXPECT_EQ(graph.getRoot()->getPath(), "NewpathStr");
    EXPECT_EQ(graph.getRoot()->getSize(), 1);
    EXPECT_EQ(graph.getRoot()->getUrl(), "NewurlStr");
    EXPECT_EQ(graph.getRoot()->getHtmlUrl(), "Newhtml_urlStr");
    EXPECT_EQ(graph.getRoot()->getGitUrl(), "Newgit_urlStr");
    EXPECT_EQ(graph.getRoot()->getDownloadUrl(), "Newdownload_urlStr");
    EXPECT_EQ(graph.getRoot()->getType(), ItemEnumType::UNKNOWN);
}

TEST_F(FolderGraphTest, valdateExtractPropertyBehaviorToRetreveValuesFromNode)
{
    FolderGraph graph(root);

    EXPECT_EQ(std::get<std::string>(graph.extractProperty(graph.getRoot(), PropertySelector::Name)),
              "root");
    EXPECT_EQ(std::get<std::filesystem::path>(
                  graph.extractProperty(graph.getRoot(), PropertySelector::Path)),
              "pathStr");
    EXPECT_EQ(
        std::get<unsigned int>(graph.extractProperty(graph.getRoot(), PropertySelector::Size)), 0);
    EXPECT_EQ(std::get<std::string>(graph.extractProperty(graph.getRoot(), PropertySelector::Url)),
              "urlStr");
    EXPECT_EQ(
        std::get<std::string>(graph.extractProperty(graph.getRoot(), PropertySelector::HtmlUrl)),
        "html_urlStr");
    EXPECT_EQ(
        std::get<std::string>(graph.extractProperty(graph.getRoot(), PropertySelector::GitUrl)),
        "git_urlStr");
    EXPECT_EQ(std::get<std::string>(
                  graph.extractProperty(graph.getRoot(), PropertySelector::DownloadUrl)),
              "download_urlStr");
    EXPECT_EQ(
        std::get<ItemEnumType>(graph.extractProperty(graph.getRoot(), PropertySelector::Type)),
        ItemEnumType::UNKNOWN);
}

TEST_F(FolderGraphTest, RetreveEmptyVectorWithInvalidEntry)
{
    FolderGraph graph(root);

    const auto resultDFS = graph.dfsToJson(nullptr, PropertySelector::Type);
    const auto resultBFS = graph.dfsToJson(nullptr, PropertySelector::Type);

    EXPECT_TRUE(resultDFS.empty());
    EXPECT_TRUE(resultBFS.empty());
}

TEST_F(FolderGraphTest, RetreveTypeOfRootNodeGraphDFS)
{
    FolderGraph graph(root);

    const std::vector<FolderGraph::NamedProperty> expectedVector = {
        {"root", ItemEnumType::UNKNOWN}  // Type == "typeStr"
    };

    const auto result = graph.dfsToJson(graph.getRoot(), PropertySelector::Type);

    EXPECT_EQ(result.size(), expectedVector.size());
    EXPECT_EQ(result[0], expectedVector[0]);
}

TEST_F(FolderGraphTest, RetreveTypeOfGraphWithChildrenDFS)
{
    FolderGraph graph(root);
    graph.addEdge(graph.getRoot(), child1);
    graph.addEdge(graph.getRoot(), child2);

    const std::vector<FolderGraph::NamedProperty> expectedVector = {
        {"root", ItemEnumType::UNKNOWN},    // Type == "typeStr"
        {"child1", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child2", ItemEnumType::UNKNOWN}   // Type == "typeStr"
    };

    const auto result = graph.dfsToJson(graph.getRoot(), PropertySelector::Type);

    EXPECT_EQ(result.size(), expectedVector.size());

    for (size_t i = 0; i < result.size(); ++i)
    {
        EXPECT_EQ(result[i], expectedVector[i]);
    }
}

TEST_F(FolderGraphTest, RetreveTypeOfGraphWithChildren3layersDFS)
{
    FolderGraph graph(root);
    graph.addEdge(graph.getRoot(), child1);
    graph.addEdge(graph.getRoot(), child2);
    graph.addEdge(graph.getRoot()->getChildren()[0], child3);
    graph.addEdge(graph.getRoot()->getChildren()[0], child4);

    const std::vector<FolderGraph::NamedProperty> expectedVector = {
        {"root", ItemEnumType::UNKNOWN},    // Type == "typeStr"
        {"child1", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child3", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child4", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child2", ItemEnumType::UNKNOWN}   // Type == "typeStr"
    };

    const auto result = graph.dfsToJson(graph.getRoot(), PropertySelector::Type);

    EXPECT_EQ(result.size(), expectedVector.size());

    for (size_t i = 0; i < result.size(); ++i)
    {
        EXPECT_EQ(result[i], expectedVector[i]);
    }
}

TEST_F(FolderGraphTest, RetreveTypeOfRootNodeGraphBFS)
{
    FolderGraph graph(root);

    const std::vector<FolderGraph::NamedProperty> expectedVector = {
        {"root", ItemEnumType::UNKNOWN}  // Type == "typeStr"
    };

    const auto result = graph.bfsToJson(graph.getRoot(), PropertySelector::Type);

    EXPECT_EQ(result.size(), expectedVector.size());
    EXPECT_EQ(result[0], expectedVector[0]);
}

TEST_F(FolderGraphTest, RetreveTypeOfGraphWithChildrenBFS)
{
    FolderGraph graph(root);
    graph.addEdge(graph.getRoot(), child1);
    graph.addEdge(graph.getRoot(), child2);

    const std::vector<FolderGraph::NamedProperty> expectedVector = {
        {"root", ItemEnumType::UNKNOWN},    // Type == "typeStr"
        {"child1", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child2", ItemEnumType::UNKNOWN}   // Type == "typeStr"
    };

    const auto result = graph.bfsToJson(graph.getRoot(), PropertySelector::Type);

    EXPECT_EQ(result.size(), expectedVector.size());

    for (size_t i = 0; i < result.size(); ++i)
    {
        EXPECT_EQ(result[i], expectedVector[i]);
    }
}

TEST_F(FolderGraphTest, RetreveTypeOfGraphWithChildren3layersBFS)
{
    FolderGraph graph(root);
    graph.addEdge(graph.getRoot(), child1);
    graph.addEdge(graph.getRoot(), child2);
    graph.addEdge(graph.getRoot()->getChildren()[0], child3);
    graph.addEdge(graph.getRoot()->getChildren()[0], child4);

    const std::vector<FolderGraph::NamedProperty> expectedVector = {
        {"root", ItemEnumType::UNKNOWN},    // Type == "typeStr"
        {"child1", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child2", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child3", ItemEnumType::UNKNOWN},  // Type == "typeStr"
        {"child4", ItemEnumType::UNKNOWN}   // Type == "typeStr"
    };

    const auto result = graph.bfsToJson(graph.getRoot(), PropertySelector::Type);

    EXPECT_EQ(result.size(), expectedVector.size());

    for (size_t i = 0; i < result.size(); ++i)
    {
        EXPECT_EQ(result[i], expectedVector[i]);
    }
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