#include "../../src/ProcessSourceFiles/ProcessFiles.h"

#include <gtest/gtest.h>

class DownloadFilesTest : public ::testing::Test
{
   protected:
    // Can't be a real one because it's unit test not integration.
    // Create mocks if needs to download things
    std::string testURL = "https://github.com/hugomdq/my-cool-repo/tree/main/src";
};

TEST_F(DownloadFilesTest, ValidateConstructorWithASimpleTestURL)
{
    EXPECT_EQ(DownloadFiles(testURL).getOriginalURL(), testURL);
}

TEST_F(DownloadFilesTest, EmptyURLStringPassedToTheExplicityThrowsInvalidArgumentException)
{
    EXPECT_THROW(DownloadFiles("").getOriginalURL(), std::invalid_argument);
}
