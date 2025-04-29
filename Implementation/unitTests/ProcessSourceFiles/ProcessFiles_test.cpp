#include "../../src/ProcessSourceFiles/ProcessFiles.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

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
        std::cout << "[MockHttpClient] Fetching URL: " << url << std::endl;
        response = m_mockResponse;
        return m_shouldSucceed;
    }

    void downloadFile(
        const std::string& url, const std::string& outputPath,
        std::optional<size_t (*)(void*, size_t, size_t, void*)> writeCallback) override
    {
    }

    void setShouldSucceed(bool shouldSucceed)
    {
        m_shouldSucceed = shouldSucceed;
    }

    void setMockResponse(const std::string& mockResponse)
    {
        m_mockResponse = mockResponse;
    }
};

class DownloadFilesTest : public ::testing::Test
{
   protected:
    // Can't be a real one because it's unit test not integration.
    // Create mocks if needs to download things
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
        "url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/File1.cpp?ref=5---Download-gitHub-files-in-a-local-temp-folder",
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
        "url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1?ref=5---Download-gitHub-files-in-a-local-temp-folder",
        "html_url": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder1",
        "git_url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/trees/48f33dcb5d6ca7dca35c1c9fa5eea4206c5fdcda",
        "download_url": null,
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
        "url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/contents/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2?ref=5---Download-gitHub-files-in-a-local-temp-folder",
        "html_url": "https://github.com/HugorTorquato/MBA-TCC/tree/5---Download-gitHub-files-in-a-local-temp-folder/Implementation/observability/source_code_for_testing/ProcessSourceFiles/EmptyProjectFoldeStructure/Folder2",
        "git_url": "https://api.github.com/repos/HugorTorquato/MBA-TCC/git/trees/4d438c58d6ad07c1cc7f682628854a07d7a38ad7",
        "download_url": null,
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
    EXPECT_EQ(DownloadFiles(testURL, std::move(mockClient)).getOriginalURL(), testURL);
}

TEST_F(DownloadFilesTest, EmptyURLStringPassedToTheExplicityThrowsInvalidArgumentException)
{
    EXPECT_THROW(DownloadFiles(customEmptyUrl, std::move(mockClient)).getOriginalURL(),
                 std::invalid_argument);
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder_testURL)
{
    EXPECT_TRUE(DownloadFiles(testURL, std::move(mockClient)).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder_testURLToFile)
{
    EXPECT_TRUE(DownloadFiles(testURLToFile, std::move(mockClient)).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder_testURLToFolder)
{
    EXPECT_TRUE(DownloadFiles(testURLToFolder, std::move(mockClient)).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsANotValidGitHubUrl)
{
    EXPECT_FALSE(DownloadFiles(testURLNotValid, std::move(mockClient)).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, ValidUrlReturnsTrue)
{
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_TRUE(downlaodFilesObj.isValidUrl());
}

TEST_F(DownloadFilesTest, InvalidUrlReturnsFalse)
{
    mockClient->setShouldSucceed(false);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_FALSE(downlaodFilesObj.isValidUrl());
}

TEST_F(DownloadFilesTest, InvalidUrlReturnsFalseForDifferentUrlFromGitHubSource)
{
    mockClient->setShouldSucceed(false);
    DownloadFiles downlaodFilesObj(testURLNotValid, std::move(mockClient));

    EXPECT_FALSE(downlaodFilesObj.isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsFalseIfNotValidURL)
{
    EXPECT_FALSE(DownloadFiles(testURLNotValid, std::move(mockClient)).isFolder());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsTrueIfValidURLFolder)
{
    EXPECT_TRUE(DownloadFiles(testURLToFolder, std::move(mockClient)).isFolder());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsFalseIfValidURLFile)
{
    EXPECT_FALSE(DownloadFiles(testURLToFile, std::move(mockClient)).isFolder());
}

TEST_F(DownloadFilesTest, DoNotParseUrlIfNotFromGitHub)
{
    DownloadFiles downlaodFilesObj(testURLNotValid, std::move(mockClient));
    downlaodFilesObj.parseURL(downlaodFilesObj.getOriginalURL());

    EXPECT_EQ(downlaodFilesObj.getBranch(), "");
    EXPECT_EQ(downlaodFilesObj.getPath(), "");
    EXPECT_EQ(downlaodFilesObj.getRepo(), "");
    EXPECT_EQ(downlaodFilesObj.getUser(), "");
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFolder)
{
    DownloadFiles downlaodFilesObj(testURLToFolder, std::move(mockClient));
    downlaodFilesObj.parseURL(testURLToFolder);

    EXPECT_EQ(downlaodFilesObj.getBranch(), branch);
    EXPECT_EQ(downlaodFilesObj.getPath(), pathtofolder);
    EXPECT_EQ(downlaodFilesObj.getRepo(), repo);
    EXPECT_EQ(downlaodFilesObj.getUser(), user);
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFile)
{
    DownloadFiles downlaodFilesObj(testURLToFile, std::move(mockClient));
    downlaodFilesObj.parseURL(testURLToFile);

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
    GitHubUrlInfo urlInfo{.m_branch = "branch321",
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

    EXPECT_EQ(downlaodFilesObj.listGitHubContentFromURL(nullUrl), expectedResponse);
}

TEST_F(DownloadFilesTest, downloadFakeFolderStructureFromGitHub)
{
    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedRealResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_TRUE(downlaodFilesObj.downloadURLContentIntoTempFolder());
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

TEST_F(DownloadFilesTest, recursivelyProcessJsonResponse)
{
    const std::string expectedResponse = R"(
    [
        {"name": "File1.cpp"},
        {"name": "Folder1"},
        {"name": "Folder2"}
    ]
    )";
    mockClient->setShouldSucceed(true);
    mockClient->setMockResponse(expectedResponse);
    DownloadFiles downlaodFilesObj(testURL, std::move(mockClient));

    EXPECT_TRUE(downlaodFilesObj.downloadURLContentIntoTempFolder());
}
