#include "../../src/ProcessSourceFiles/ProcessFiles.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

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
};

TEST_F(DownloadFilesTest, ValidateConstructorWithASimpleTestURL)
{
    EXPECT_EQ(DownloadFiles(testURL).getOriginalURL(), testURL);
}

TEST_F(DownloadFilesTest, EmptyURLStringPassedToTheExplicityThrowsInvalidArgumentException)
{
    EXPECT_THROW(DownloadFiles(customEmptyUrl).getOriginalURL(), std::invalid_argument);
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder)
{
    EXPECT_TRUE(DownloadFiles(testURL).isUrlFromGitHub());
    EXPECT_TRUE(DownloadFiles(testURLToFile).isUrlFromGitHub());
    EXPECT_TRUE(DownloadFiles(testURLToFolder).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsANotValidGitHubUrl)
{
    EXPECT_FALSE(DownloadFiles(testURLNotValid).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsFalseIfNotValidURL)
{
    EXPECT_FALSE(DownloadFiles(testURLNotValid).isFolder());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsTrueIfValidURLFolder)
{
    EXPECT_TRUE(DownloadFiles(testURLToFolder).isFolder());
}

TEST_F(DownloadFilesTest, VerfyIfFolderOrFileIsFalseIfValidURLFile)
{
    EXPECT_FALSE(DownloadFiles(testURLToFile).isFolder());
}

TEST_F(DownloadFilesTest, DoNotParseUrlIfNotFromGitHub)
{
    DownloadFiles downlaodFilesObj(testURLNotValid);
    downlaodFilesObj.parseURL();

    EXPECT_EQ(downlaodFilesObj.getBranch(), "");
    EXPECT_EQ(downlaodFilesObj.getPath(), "");
    EXPECT_EQ(downlaodFilesObj.getRepo(), "");
    EXPECT_EQ(downlaodFilesObj.getUser(), "");
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFolder)
{
    DownloadFiles downlaodFilesObj(testURLToFolder);
    downlaodFilesObj.parseURL();

    EXPECT_EQ(downlaodFilesObj.getBranch(), branch);
    EXPECT_EQ(downlaodFilesObj.getPath(), pathtofolder);
    EXPECT_EQ(downlaodFilesObj.getRepo(), repo);
    EXPECT_EQ(downlaodFilesObj.getUser(), user);
}

TEST_F(DownloadFilesTest, RetrieveGitHubUrlInfoFromUrlWithFile)
{
    DownloadFiles downlaodFilesObj(testURLToFile);
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

    DownloadFiles downlaodFilesObj(customUrl);
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

    DownloadFiles downlaodFilesObj(customMissingagumentsUrl);
    downlaodFilesObj.parseURL();

    EXPECT_THROW(downlaodFilesObj.listGitHubContentFromURL(), std::invalid_argument);
}