#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "../../../src/ProcessSourceFiles/RepoURLFactory.h"

class RepoURLFactoryTest : public ::testing::Test
{
   protected:
    const std::string emptyUrl = R"()";
    const std::string invalidUrl = R"(INVALID)";
    const std::string validApiUrl =
        R"(https://api.github.com/repos/user/repo/contents/folder/file.cpp?ref=main)";
    const std::string validWebUrl = R"(https://github.com/user/repo/tree/main/folder)";
};

TEST_F(RepoURLFactoryTest, exceptionIfInvalidEmptyUrl)
{
    EXPECT_THROW(RepoURLFactory::createRepoURL(emptyUrl), std::invalid_argument);
    EXPECT_THROW(RepoURLFactory::createRepoURL(invalidUrl), std::invalid_argument);
}

TEST_F(RepoURLFactoryTest, VerifyIfValidApiURL)
{
    auto factory = RepoURLFactory::createRepoURL(validApiUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_TRUE(factory->isValidUrl(validApiUrl));
}

TEST_F(RepoURLFactoryTest, VerifyIfValidWebURL)
{
    auto factory = RepoURLFactory::createRepoURL(validWebUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_TRUE(factory->isValidUrl(validWebUrl));
}

// Test the get regexp... If anyone changes it i need to double check