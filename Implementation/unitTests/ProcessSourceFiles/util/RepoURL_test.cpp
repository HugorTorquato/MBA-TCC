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
    const std::string validFolderWebUrl =
        R"(https://github.com/user/repo/tree/branch/path/to/folder)";
    const std::string validFileWebUrl =
        R"(https://github.com/user/repo/blob/branch/path/to/file.cpp)";
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

TEST_F(RepoURLFactoryTest, VerifyIfGetRegexpIsValidaPIuRL)
{
    auto factory = RepoURLFactory::createRepoURL(validApiUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_EQ(
        factory->getRegexp(),
        R"(https:\/\/api\.github\.com\/repos\/([^\/]+)\/([^\/]+)\/contents\/(.*?)(?:\?ref=(.*))?)");
}

TEST_F(RepoURLFactoryTest, VerifyIfGetRegexpIsValidWebUrl)
{
    auto factory = RepoURLFactory::createRepoURL(validWebUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_EQ(factory->getRegexp(),
              R"(https:\/\/github\.com\/([^\/]+)\/([^\/]+)\/(tree|blob)\/([^\/]+)(\/(.*))?)");
}

TEST_F(RepoURLFactoryTest, VerifyIfIsFromGitHub)
{
    EXPECT_TRUE(RepoURLFactory::isFromGtHub(validApiUrl));
    EXPECT_TRUE(RepoURLFactory::isFromGtHub(validWebUrl));
    EXPECT_THROW(RepoURLFactory::isFromGtHub(invalidUrl), std::invalid_argument);
    EXPECT_FALSE(RepoURLFactory::isFromGtHub(emptyUrl));
}

TEST_F(RepoURLFactoryTest, VerifyConstructors)
{
    auto factory = RepoURLFactory::createRepoURL(validApiUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_EQ(factory->getBranch(), "main");
    EXPECT_EQ(factory->getPath(), "");
    EXPECT_EQ(factory->getRepo(), "repo");
    EXPECT_EQ(factory->getUser(), "user");

    factory = RepoURLFactory::createRepoURL(validWebUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_EQ(factory->getBranch(), "main");
    EXPECT_EQ(factory->getPath(), "folder");
    EXPECT_EQ(factory->getRepo(), "repo");
    EXPECT_EQ(factory->getUser(), "user");
}

TEST_F(RepoURLFactoryTest, VerifyIfIsFolder)
{
    auto factory = RepoURLFactory::createRepoURL(validApiUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_FALSE(factory->isFolder(validApiUrl));

    factory = RepoURLFactory::createRepoURL(validFolderWebUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_TRUE(factory->isFolder(validFolderWebUrl));

    factory = RepoURLFactory::createRepoURL(validFileWebUrl);
    EXPECT_TRUE(factory != nullptr);
    EXPECT_FALSE(factory->isFolder(validFileWebUrl));
}