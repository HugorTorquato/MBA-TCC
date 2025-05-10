#include "../../src/ProcessSourceFiles/ProcessFiles.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>  // Required for std::ofstream
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

namespace fs = std::filesystem;

class MockHttpClient : public IHttpClient
{
   private:
    bool m_shouldSucceed;
    std::string m_mockResponse;
    std::vector<std::string> m_mockResponses;
    unsigned currentIndex = 0;

    std::string m_fileToDownload;
    std::string m_filecontent;

   public:
    // Constructor to configure behavior
    MockHttpClient(bool shouldSucceed, const std::string& mockResponse)
        : m_shouldSucceed(shouldSucceed), m_mockResponse(mockResponse)
    {
    }

    ~MockHttpClient() = default;

    bool getResponseFronUrl(
        const std::string& url, std::string& response,
        std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback) override
    {
        // std::cout << "[MockHttpClient] Fetching URL: " << url << std::endl;
        if (m_mockResponses.empty())
            response = m_mockResponse;
        else if (currentIndex < m_mockResponses.size())
            response = m_mockResponses[currentIndex++];
        else
            response = "{}";  // Default empty JSON

        // std::cout << "[MockHttpClient] Fetching response: " << response << std::endl;
        return m_shouldSucceed;
    }

    bool downloadFile(
        const std::string& url, const std::string& outputPath,
        std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback) override
    {
        // Simulate downloading a file by just returning true
        // std::cout << "[MockHttpClient] Downloading file from URL: " << url
        //           << " to output path: " << outputPath << std::endl;

        fs::create_directories(fs::path(outputPath).parent_path());

        // Create and write to the file
        std::ofstream outFile(outputPath);
        if (!outFile)
        {
            throw std::runtime_error("Failed to create file: " + outputPath);
        }

        outFile << m_filecontent;
        outFile.close();

        return m_shouldSucceed;
    }

    void setShouldSucceed(bool shouldSucceed)
    {
        m_shouldSucceed = shouldSucceed;
    }

    void setMockResponse(const std::string& mockResponse)
    {
        m_mockResponse = mockResponse;
    }

    void includeInMockResponses(const std::string& mockResponse)
    {
        m_mockResponses.push_back(mockResponse);
    }

    void setCurrentIndex(unsigned index)
    {
        currentIndex = index;
    }

    void setFilecontent(const std::string& content)
    {
        m_filecontent = content;
    }
};

class DownloadFilesTest : public ::testing::Test
{
   protected:
    // Can't be a real one because it's unit test not integration.
    // Create mocks if needs to download things
    const std::string testApiURL =
        "https://api.github.com/repos/user123/repoABC/contents/path/to/file.cpp?ref=main";
    const std::string testURL =
        "https://github.com/HugorTorquato/MBA-TCC/tree/main/Implementation/src";
    const std::string testURLNotValid = "https://BLA.com/hugomdq/my-cool-repo/tree/main/src";
    const std::string testURLToFile = "https://github.com/user/repo/blob/branch/path/to/file.cpp";
    const std::string testURLToFolder = "https://github.com/user/repo/tree/branch/path/to/folder";
    const std::string customEmptyUrl = "";
    const std::string customMissingagumentsUrl =
        "https://github.com//repo123/tree/branch321/path123321/to/folder";
    const std::string customUrl =
        "https://github.com/torquato/repo123/tree/branch321/path123321/to/folder";

    const std::string branch = "branch";
    const std::string pathtofolder = "path/to/folder";
    const std::string pathtofile = "path/to/file.cpp";
    const std::string repo = "repo";
    const std::string user = "user";

    const std::nullopt_t nullUrl = std::nullopt;

    const std::string expectedRealResponse = R"(
    [
        {
        "name": "File1.cpp",
        "path": "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp",
        "sha": "e69de29bb2d1d6434b8b29ae775ad8c5391",
        "size": 0,
        "url": "",
        "html_url": "https://github.com/HugorTorquato/MBA-TCC/blob/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp",
        "git_url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/blobs/e69de29bb2d1d6434b8b29ae775ad8c5391",
        "download_url": "https://raw.githubusercontent.com/HugorTorquato/MBA-TCC/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp",
        "type": "file",
        "_links": {
            "self": "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp?ref=5---Download-gitHub-files-in-a-local-temp-folder",
            "git": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/blobs/e69de29bb2d1d6434b8b29ae775ad8c5391",
            "html": "https://github.com/HugorTorquato/MBA-TCC/blob/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp"
        }
        },
        {
        "name": "Folder1",
        "path": "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1",
        "sha": "48f33dcb5d6ca7dca35c1c9fa5eea4206c5fdcda",
        "size": 0,
        "url": "",
        "html_url": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1",
        "git_url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/trees/48f33dcb5d6ca7dca35c1c9fa5eea4206c5fdcda",
        "download_url": "null",
        "type": "dir",
        "_links": {
            "self": "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1?ref=5---Download-gitHub-files-in-a-local-temp-folder",
            "git": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/trees/48f33dcb5d6ca7dca35c1c9fa5eea4206c5fdcda",
            "html": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1"
        }
        },
        {
        "name": "Folder2",
        "path": "Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2",
        "sha": "4d438c58d6ad07c1cc7f682628854a07d7a38ad7",
        "size": 0,
        "url": "",
        "html_url": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2",
        "git_url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/trees/4d438c58d6ad07c1cc7f682628854a07d7a38ad7",
        "download_url": "null",
        "type": "dir",
        "_links": {
            "self": "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2?ref=5---Download-gitHub-files-in-a-local-temp-folder",
            "git": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/trees/4d438c58d6ad07c1cc7f682628854a07d7a38ad7",
            "html": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2"
        }
        }
    ]
    )";

   protected:
    std::unique_ptr<MockHttpClient> mockClient;  // Member to persist across tests
    const std::string tempFolder = "/app/temp/";

    void SetUp() override
    {
        mockClient = std::make_unique<MockHttpClient>(true, "OK response from server");
    }

    void TearDown() override
    {
        // No need to clean mockClient, std::unique_ptr<> handles it.
        fs::remove_all(tempFolder);
    }
};

TEST_F(DownloadFilesTest, ValidateConstructorWithASimpleTestURL)
{
    // Must dereference the pointer
    DownloadFiles downloader(testURL, std::move(mockClient));
    EXPECT_EQ(downloader.getOriginalURL(), testURL);
}

TEST_F(DownloadFilesTest, EmptyURLStringPassedToTheExplicityThrowsInvalidArgumentException)
{
    EXPECT_THROW(DownloadFiles(customEmptyUrl, std::move(mockClient)).getOriginalURL(),
                 std::invalid_argument);
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder_testURL)
{
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_TRUE(urlInfo->isFromGtHub(testURL));
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder_testURLToFile)
{
    DownloadFiles downlaodFilesObj(testURLToFile, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_TRUE(urlInfo->isFromGtHub(testURLToFile));
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder_testURLToFolder)
{
    DownloadFiles downlaodFilesObj(testURLToFolder, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_TRUE(urlInfo->isFromGtHub(testURLToFolder));
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsANotValidGitHubUrl)
{
    EXPECT_THROW(DownloadFiles(testURLNotValid, std::move(mockClient)), std::invalid_argument);
}

TEST_F(DownloadFilesTest, ValidUrlReturnsTrue)
{
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_TRUE(urlInfo->isValidUrl(testURL));
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, InvalidUrlReturnsFalseForDifferentUrlFromGitHubSource)
{
    EXPECT_THROW(DownloadFiles(testURLNotValid, std::move(mockClient)), std::invalid_argument);
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsTrueIfValidURLFolder)
{
    DownloadFiles downlaodFilesObj(testURLToFolder, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_TRUE(urlInfo->isFolder(testURLToFolder));
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsFalseIfValidURLFile)
{
    DownloadFiles downlaodFilesObj(testURLToFile, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_FALSE(urlInfo->isFolder(testURLToFile));
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFolder)
{
    DownloadFiles downlaodFilesObj(testURLToFolder, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_EQ(downlaodFilesObj.getBranch(), "branch");
        EXPECT_EQ(downlaodFilesObj.getPath(), "path/to/folder");
        EXPECT_EQ(downlaodFilesObj.getRepo(), "repo");
        EXPECT_EQ(downlaodFilesObj.getUser(), "user");
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFile)
{
    DownloadFiles downlaodFilesObj(testURLToFile, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        EXPECT_EQ(downlaodFilesObj.getBranch(), "branch");
        EXPECT_EQ(downlaodFilesObj.getPath(), "path/to/file.cpp");
        EXPECT_EQ(downlaodFilesObj.getRepo(), "repo");
        EXPECT_EQ(downlaodFilesObj.getUser(), "user");
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, RetreveExpectedEndointFromParsedInputUrl)
{
    struct APIUrlInfo
    {
        std::string m_branch;
        std::string m_path;
        std::string m_repo;
        std::string m_user;
    };

    APIUrlInfo urlInfo{.m_branch = "branch321",
                       .m_path = "path123321/to/folder",
                       .m_repo = "repo123",
                       .m_user = "torquato"};

    DownloadFiles downlaodFilesObj(customUrl, std::move(mockClient));
    // downlaodFilesObj.parseURL(downlaodFilesObj.getOriginalURL());

    std::string expectedEndpoint = "https://api.github.com/repos/" + urlInfo.m_user + "/" +
                                   urlInfo.m_repo + "/contents/" + urlInfo.m_path +
                                   "?ref=" + urlInfo.m_branch;

    EXPECT_EQ(downlaodFilesObj.getEndpointToListFilesFromGitHub(downlaodFilesObj.getOriginalURL()),
              expectedEndpoint);
}

TEST_F(DownloadFilesTest, ThrowInvaldArgumentExceptionIfNotValidEndpoint)
{
    struct WebUrlInfo
    {
        std::string m_branch;
        std::string m_path;
        std::string m_repo;
        std::string m_user;
    };

    WebUrlInfo urlInfo{.m_branch = "branch321",
                       .m_path = "path123321/to/folder",
                       .m_repo = "repo123",
                       .m_user = "torquato"};

    DownloadFiles downlaodFilesObj(customMissingagumentsUrl, std::move(mockClient));

    EXPECT_THROW(downlaodFilesObj.listGitHubContentFromURL(nullUrl), std::invalid_argument);
}

TEST_F(DownloadFilesTest, RetrieveEmptyGitHubListOfFiles)
{
    const std::string expectedResponse = "";
    mockClient->setMockResponse(expectedResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_EQ(downlaodFilesObj.listGitHubContentFromURL(testURL), expectedResponse);
}

TEST_F(DownloadFilesTest, downloadFakeFolderStructureFromGitHub)
{
    const std::string expectedResponse =
        "{\"File1.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/"
        "EmptyProjectFoldeStructure/File1.cpp\":\"Implementation/observability/"
        "source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/"
        "File1.cpp\",\"root:\":\"\"}";
    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedRealResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    const auto response = downlaodFilesObj.downloadURLContentIntoTempFolder();
    EXPECT_EQ(response.dump(), expectedResponse);
}

TEST_F(DownloadFilesTest, downloadFakeInvalidstringConversionToJsonFolderStructureFromGitHub)
{
    const std::string expectedResponse = R"({[{"name": "File1.cpp"}]})";
    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_THROW(downlaodFilesObj.downloadURLContentIntoTempFolder(), std::runtime_error);
}

TEST_F(DownloadFilesTest, downloadFakeEmptyFolderStructureFromGitHub)
{
    const std::string expectedResponse = R"("BLA")";
    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_THROW(downlaodFilesObj.downloadURLContentIntoTempFolder(), std::runtime_error);
}

TEST_F(DownloadFilesTest, recursivelyProcessJsonResponseMissingItemTypeShouldNotPopulateGraph)
{
    const std::string expectedResponse = R"(
    [
        {"name": "File1.cpp"}
    ]
    )";

    const std::string expectedDownloadJSONResponse = "{\"root:\":\"\"}";

    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    const auto response = downlaodFilesObj.downloadURLContentIntoTempFolder();

    EXPECT_EQ(response.dump(), expectedDownloadJSONResponse);

    auto root = downlaodFilesObj.getFolderGraph().getRoot();
    EXPECT_EQ(root->getName(), "root");
    EXPECT_TRUE(root->getChildren().empty());
}

TEST_F(DownloadFilesTest, recursivelyProcessJsonResponseOneFileShouldPopulateGraph)
{
    const std::string expectedJsonResponse =
        "{\"File1.cpp:File1.cpp\":\"File1.cpp\",\"root:\":\"\"}";
    const std::string expectedResponse = R"(
    [
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "File1.cpp"}
    ]
    )";
    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    const auto response = downlaodFilesObj.downloadURLContentIntoTempFolder();

    EXPECT_EQ(response.dump(), expectedJsonResponse);

    auto root = downlaodFilesObj.getFolderGraph().getRoot();
    EXPECT_EQ(root->getName(), "root");
    EXPECT_EQ(root->getChildren().size(), 1);
}

TEST_F(DownloadFilesTest, recursivelyProcessJsonResponseFolderWithInvalidURLShouldNotPopulateGraph)
{
    const std::string expectedJsonResponse =
        "{\"File1.cpp:File1.cpp\":\"File1.cpp\",\"root:\":\"\"}";
    const std::string expectedResponse = R"(
    [
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "File1.cpp"},
        {"name": "Folder1", "type": "dir", "url": ""}
    ]
    )";
    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    auto root = downlaodFilesObj.getFolderGraph().getRoot();
    const auto response = downlaodFilesObj.downloadURLContentIntoTempFolder();

    EXPECT_EQ(response.dump(), expectedJsonResponse);
    EXPECT_EQ(root->getName(), "root");
    EXPECT_EQ(root->getChildren().size(), 1);
    // EXPECT_EQ(root->getChildren()[0]->getName(), "File1.cpp");
}

TEST_F(DownloadFilesTest, MatchesOnlyGitHubApiUrls)
{
    DownloadFiles downlaodFilesObj(testApiURL, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        std::regex github_url_pattern(urlInfo->getRegexp());

        struct TestCase
        {
            std::string url;
            std::string description;
            std::vector<std::string> expectedGroups;  // capturing groups only
        };

        std::vector<TestCase> testCases = {
            {"https://api.github.com/repos/user123/repoABC/contents/path/to/file.cpp?ref=main",
             "API URL to file",
             {"user123", "repoABC", "path/to/file.cpp", "main", "", "", "", "", ""}},
            {"https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/"
             "observability/"
             "source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/"
             "File1.cpp?ref=5---Download-gitHub-files-in-a-local-temp-folder",
             "API URL with long branch name",
             {"HugorTorquato", "MBA-TCC",
              "Implementation/observability/source_code_for_testing/ProcessSourceFiles/"
              "EmptyProjectFoldeStructure/File1.cpp",
              "5---Download-gitHub-files-in-a-local-temp-folder", "", "", "", "", ""}}};

        for (const auto& test : testCases)
        {
            std::smatch match;
            ASSERT_TRUE(std::regex_match(test.url, match, github_url_pattern))
                << "Failed to match: " << test.url;
        }
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, MatchesOnlyGitHubWebUrls)
{
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    if (auto urlInfo = downlaodFilesObj.getUrlInfo(); urlInfo != nullptr)
    {
        std::regex github_url_pattern(urlInfo->getRegexp());
        struct TestCase
        {
            std::string url;
            std::string description;
            std::vector<std::string> expectedGroups;  // only the capturing groups
        };

        std::vector<TestCase> testCases = {
            {"https://github.com/HugorTorquato/MBA-TCC/tree/main/Implementation/src",
             "Web URL to folder (custom)",
             {"HugorTorquato", "MBA-TCC", "tree", "main", "Implementation/src"}},
            {"https://github.com/user/repo/blob/dev/path/to/file.cpp",
             "Web URL to file",
             {"user", "repo", "blob", "dev", "path/to/file.cpp"}},
            {"https://github.com/user/repo/tree/main",
             "Web URL without path",
             {"user", "repo", "tree", "main", ""}}};

        for (const auto& test : testCases)
        {
            std::smatch match;
            ASSERT_TRUE(std::regex_match(test.url, match, github_url_pattern))
                << "Failed to match: " << test.url;
        }
    }
    else
    {
        FAIL() << "URL info is null";
    }
}

TEST_F(DownloadFilesTest, recursivelyProcessFolderWithValidNestedFolder)
{
    const std::string expectedJsonResponse =
        "{\"FileInsideFolder1.cpp:Folder1/FileInsideFolder1.cpp\":\"Folder1/"
        "FileInsideFolder1.cpp\",\"Folder1:\":\"\",\"root:\":\"\"}";
    const std::string firstLevelResponse = R"(
    [
        {"name": "Folder1", "type": "dir", "url":
        "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp?ref=5---Download-gitHub-files-in-a-local-temp-folder"}
    ]
    )";

    const std::string secondLevelResponse = R"(
    [
        {"name": "FileInsideFolder1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/FileInsideFolder1.cpp"}
    ]
    )";

    // Way to add diferent responses to the mock, first and second
    mockClient->setShouldSucceed(true);
    mockClient->includeInMockResponses(firstLevelResponse);
    mockClient->includeInMockResponses(secondLevelResponse);

    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    const auto response = downlaodFilesObj.downloadURLContentIntoTempFolder();

    EXPECT_EQ(response.dump(), expectedJsonResponse);

    auto root = downlaodFilesObj.getFolderGraph().getRoot();
    if (root == nullptr) FAIL() << "Root hsould not be null";
    EXPECT_EQ(root->getChildren().size(), 1);
    EXPECT_EQ(root->getChildren()[0]->getName(), "Folder1");

    auto child = downlaodFilesObj.getFolderGraph().getRoot()->getChildren()[0];
    if (child == nullptr) FAIL() << "child hsould not be null";
    EXPECT_EQ(child->getChildren().size(), 1);
    EXPECT_EQ(child->getChildren()[0]->getName(), "FileInsideFolder1.cpp");
}

TEST_F(DownloadFilesTest, recursivelyProcessFolderWithValidNestedFolderAndFile)
{
    const std::string expectedJsonResponse =
        "{\"File1.cpp:Folder1/File1.cpp\":\"Folder1/File1.cpp\",\"FileInsideFolder1.cpp:Folder1/"
        "FileInsideFolder1.cpp\":\"Folder1/"
        "FileInsideFolder1.cpp\",\"Folder1:\":\"\",\"root:\":\"\"}";
    const std::string firstLevelResponse = R"(
    [
        {"name": "Folder1", "type": "dir", "url":
        "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp?ref=5---Download-gitHub-files-in-a-local-temp-folder"},
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File1.cpp"}
    ]
    )";

    const std::string secondLevelResponse = R"(
    [
        {"name": "FileInsideFolder1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/FileInsideFolder1.cpp"}
    ]
    )";

    // Way to add diferent responses to the mock, first and second
    mockClient->setShouldSucceed(true);
    mockClient->includeInMockResponses(firstLevelResponse);
    mockClient->includeInMockResponses(secondLevelResponse);

    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    const auto response = downlaodFilesObj.downloadURLContentIntoTempFolder();

    EXPECT_EQ(response.dump(), expectedJsonResponse);

    auto root = downlaodFilesObj.getFolderGraph().getRoot();
    EXPECT_EQ(root->getChildren().size(), 2);
}

TEST_F(DownloadFilesTest, throwInvaldArgumentIfParsedNotAnArray)
{
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));
    json emptyJson = R"({})"_json;
    EXPECT_THROW(downlaodFilesObj.recursivelyDownloadFilesPopulatingGraph(emptyJson, nullptr),
                 std::invalid_argument);
}

TEST_F(DownloadFilesTest, throwInvaldArgumentIfNullParentPointer)
{
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));
    json valdArrayJson = R"(
    [
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "File1.cpp"}
    ]
    )"_json;
    EXPECT_THROW(downlaodFilesObj.recursivelyDownloadFilesPopulatingGraph(valdArrayJson, nullptr),
                 std::invalid_argument);
}

TEST_F(DownloadFilesTest, mockSimpleDownloadFromGitHubApiReturningOneFile)
{
    // The reason expectedResponse.is_array() is returning false is because you're passing a string
    // literal (inside R"( ... )") directly to the json constructor — so it parses it as a JSON
    //  string, not as an actual JSON array. To fix this, you must parse the raw JSON string
    // into a nlohmann::json object using json::parse.

    const json expectedResponse = json::parse(R"(
    [
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File1.cpp"},
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File2.cpp"}
    ]
    )");

    EXPECT_TRUE(expectedResponse.is_array());

    mockClient->setFilecontent(tempFolder + "File1.cpp");

    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    downlaodFilesObj.recursivelyDownloadFilesPopulatingGraph(
        expectedResponse, downlaodFilesObj.getFolderGraph().getRoot());

    EXPECT_TRUE(fs::exists(tempFolder + "Folder1/File1.cpp"));
    EXPECT_TRUE(fs::exists(tempFolder + "Folder1/File2.cpp"));
}

// Implement tests for folder now
TEST_F(DownloadFilesTest, mockSimpleDownloadFromGitHubApiThrowsExceptionIfNotValidURL)
{
    const json expectedResponse = json::parse(R"(
    [
        {"name": "Folder1", "type": "dir", "url": "BLA", "path": "Folder1"}
    ]
    )");

    EXPECT_TRUE(expectedResponse.is_array());

    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_THROW(downlaodFilesObj.recursivelyDownloadFilesPopulatingGraph(
                     expectedResponse, downlaodFilesObj.getFolderGraph().getRoot()),
                 std::invalid_argument);
}

TEST_F(DownloadFilesTest, mockSimpleDownloadFromGitHubApiReturningFilesAndNotAndEmtyFolder)
{
    const json expectedResponse = json::parse(R"(
    [
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File1.cpp"},
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File2.cpp"},
        {"name": "Folder1", "type": "dir", "url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/blobs/e69de29bb2d1d6434b8b29ae775ad8c5391", "path": "Folder2"}
    ]
    )");

    EXPECT_TRUE(expectedResponse.is_array());

    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    downlaodFilesObj.recursivelyDownloadFilesPopulatingGraph(
        expectedResponse, downlaodFilesObj.getFolderGraph().getRoot());

    EXPECT_TRUE(fs::exists(tempFolder + "Folder1/File1.cpp"));
    EXPECT_TRUE(fs::exists(tempFolder + "Folder1/File2.cpp"));
    EXPECT_FALSE(fs::exists(tempFolder + "Folder2"));  // Don't create folders, only with files
}

TEST_F(DownloadFilesTest, mockSimpleDownloadFromGitHubApiReturningFilesAndOneFolderWithFile)
{
    const json expectedResponse = json::parse(R"(
    [
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File1.cpp"},
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File2.cpp"},
        {"name": "Folder1", "type": "dir", "url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/blobs/e69de29bb2d1d6434b8b29ae775ad8c5391", "path": "Folder2"},
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder2/File1.cpp"}
    ]
    )");

    EXPECT_TRUE(expectedResponse.is_array());

    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    downlaodFilesObj.recursivelyDownloadFilesPopulatingGraph(
        expectedResponse, downlaodFilesObj.getFolderGraph().getRoot());

    EXPECT_TRUE(fs::exists(tempFolder + "Folder1/File1.cpp"));
    EXPECT_TRUE(fs::exists(tempFolder + "Folder1/File2.cpp"));
    EXPECT_TRUE(fs::exists(tempFolder + "Folder2"));  // Don't create folders, only with files
    EXPECT_TRUE(fs::exists(tempFolder + "Folder2/File1.cpp"));
}

TEST_F(DownloadFilesTest, mockSimpleDownloadFromGitHubApiReturningOnlyValidFilesAndFolders)
{
    const json expectedResponse = json::parse(R"(
    [
        {"name": "File1.cpp", "type": "file", "download_url": "BLA", "path": "Folder1/File1.cpp"},
        {"name": "File1.App", "type": "file", "download_url": "BLA", "path": "Folder1/File2.App"},
        {"name": "Folder1", "type": "dir", "url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/blobs/e69de29bb2d1d6434b8b29ae775ad8c5391", "path": "Folder2"}
    ]
    )");

    EXPECT_TRUE(expectedResponse.is_array());

    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    downlaodFilesObj.recursivelyDownloadFilesPopulatingGraph(
        expectedResponse, downlaodFilesObj.getFolderGraph().getRoot());

    EXPECT_TRUE(fs::exists(tempFolder + "Folder1/File1.cpp"));
    EXPECT_FALSE(fs::exists(tempFolder + "Folder1/File2.App"));  // .App not supported
    EXPECT_FALSE(fs::exists(tempFolder + "Folder2"));  // Don't create folders, only with files
}