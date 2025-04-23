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
    std::string testURLToFileToFile = "https://github.com/user/repo/blob/branch/path/to/file.cpp";
    std::string testURLToFileToFolder = "https://github.com/user/repo/tree/branch/path/to/folder";
};

TEST_F(DownloadFilesTest, ValidateConstructorWithASimpleTestURL)
{
    EXPECT_EQ(DownloadFiles(testURL).getOriginalURL(), testURL);
}

TEST_F(DownloadFilesTest, EmptyURLStringPassedToTheExplicityThrowsInvalidArgumentException)
{
    EXPECT_THROW(DownloadFiles("").getOriginalURL(), std::invalid_argument);
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsAValidGitHubUrlFileOrFolder)
{
    EXPECT_TRUE(DownloadFiles(testURL).isUrlFromGitHub());
    EXPECT_TRUE(DownloadFiles(testURLToFileToFile).isUrlFromGitHub());
    EXPECT_TRUE(DownloadFiles(testURLToFileToFolder).isUrlFromGitHub());
}

TEST_F(DownloadFilesTest, VerifyIfUrlIsANotValidGitHubUrl)
{
    EXPECT_FALSE(DownloadFiles(testURLNotValid).isUrlFromGitHub());
}