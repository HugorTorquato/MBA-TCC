#include "../../src/ProcessSourceFiles/ProcessFiles.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

class MockHttpClient : public IHttpClient
{
   private:
    bool m_shouldSucceed;
    std::string m_mockResponse;

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
        response = m_mockResponse;
        return m_shouldSucceed;
    }
};

class DownloadFilesTest : public ::testing::Test
{
   protected:
    // Can't be a real one because it's unit test not integration.
    // Create mocks if needs to download things
    std::string testURL = "https://github.com/hugomdq/my-cool-repo/tree/main/src";
    std::string testURLNotValid = "https://BLA.com/hugomdq/my-cool-repo/tree/main/src";
    std::string testURLToFile = "https://github.com/user/repo/blob/branch/path/to/file.cpp";
    std::string testURLToFolder = "https://github.com/user/repo/tree/branch/path/to/folder";
    std::string customEmptyUrl = "";
    std::string customMissingagumentsUrl =
        "https://github.com//repo123/tree/branch321/path123321/to/folder";
    std::string customUrl =
        "https://github.com/torquato/repo123/tree/branch321/path123321/to/folder";

    std::string branch = "branch";
    std::string pathtofolder = "path/to/folder";
    std::string pathtofile = "path/to/file.cpp";
    std::string repo = "repo";
    std::string user = "user";

   protected:
    std::unique_ptr<MockHttpClient> mockClient;  // Member to persist across tests

    void SetUp() override
    {
        mockClient = std::make_unique<MockHttpClient>(true, "OK response from server");
    }

    void TearDown() override
    {
        // No need to clean mockClient, std::unique_ptr<> handles it.
    }
};

TEST_F(DownloadFilesTest, ValidateConstructorWithASimpleTestURL)
{
    // Must dereference the pointer
    EXPECT_EQ(DownloadFiles(testURL, *mockClient).getOriginalURL(), testURL);
}

TEST_F(DownloadFilesTest, EmptyURLStringPassedToTheExplicityThrowsInvalidArgumentException)
{
    EXPECT_THROW(DownloadFiles(customEmptyUrl, *mockClient).getOriginalURL(),
                 std::invalid_argument);
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder)
{
    EXPECT_TRUE(DownloadFiles(testURL, *mockClient).isUrlFromGitHub());
    EXPECT_TRUE(DownloadFiles(testURLToFile, *mockClient).isUrlFromGitHub());
    EXPECT_TRUE(DownloadFiles(testURLToFolder, *mockClient).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsANotValidGitHubUrl)
{
    EXPECT_FALSE(DownloadFiles(testURLNotValid, *mockClient).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsFalseIfNotValidURL)
{
    EXPECT_FALSE(DownloadFiles(testURLNotValid, *mockClient).isFolder());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsTrueIfValidURLFolder)
{
    EXPECT_TRUE(DownloadFiles(testURLToFolder, *mockClient).isFolder());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsFalseIfValidURLFile)
{
    EXPECT_FALSE(DownloadFiles(testURLToFile, *mockClient).isFolder());
}

TEST_F(DownloadFilesTest, DoNotParseUrlIfNotFromGitHub)
{
    DownloadFiles downlaodFilesObj(testURLNotValid, *mockClient);
    downlaodFilesObj.parseURL();

    EXPECT_EQ(downlaodFilesObj.getBranch(), "");
    EXPECT_EQ(downlaodFilesObj.getPath(), "");
    EXPECT_EQ(downlaodFilesObj.getRepo(), "");
    EXPECT_EQ(downlaodFilesObj.getUser(), "");
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFolder)
{
    DownloadFiles downlaodFilesObj(testURLToFolder, *mockClient);
    downlaodFilesObj.parseURL();

    EXPECT_EQ(downlaodFilesObj.getBranch(), branch);
    EXPECT_EQ(downlaodFilesObj.getPath(), pathtofolder);
    EXPECT_EQ(downlaodFilesObj.getRepo(), repo);
    EXPECT_EQ(downlaodFilesObj.getUser(), user);
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFile)
{
    DownloadFiles downlaodFilesObj(testURLToFile, *mockClient);
    downlaodFilesObj.parseURL();

    EXPECT_EQ(downlaodFilesObj.getBranch(), branch);
    EXPECT_EQ(downlaodFilesObj.getPath(), pathtofile);
    EXPECT_EQ(downlaodFilesObj.getRepo(), repo);
    EXPECT_EQ(downlaodFilesObj.getUser(), user);
}

TEST_F(DownloadFilesTest, RetreveExpectedEndointFromParsedInputUrl)
{
    GitHubUrlInfo urlInfo{.m_branch = "branch321",
                          .m_path = "path123321/to/folder",
                          .m_repo = "repo123",
                          .m_user = "torquato"};

    DownloadFiles downlaodFilesObj(customUrl, *mockClient);
    downlaodFilesObj.parseURL();

    std::string expectedEndpoint = "https://api.github.com/repos/" + urlInfo.m_user + "/" +
                                   urlInfo.m_repo + "/contents/" + urlInfo.m_path +
                                   "?ref=" + urlInfo.m_branch;

    EXPECT_EQ(downlaodFilesObj.getEndpointToListFilesFromGitHub(), expectedEndpoint);
}

TEST_F(DownloadFilesTest, ThrowInvaldArgumentExceptionIfNotValidEndpoint)
{
    GitHubUrlInfo urlInfo{.m_branch = "branch321",
                          .m_path = "path123321/to/folder",
                          .m_repo = "repo123",
                          .m_user = "torquato"};

    DownloadFiles downlaodFilesObj(customMissingagumentsUrl, *mockClient);
    downlaodFilesObj.parseURL();

    EXPECT_THROW(downlaodFilesObj.listGitHubContentFromURL(), std::invalid_argument);
}