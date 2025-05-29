#include "../../src/ProcessSourceFiles/ScannerForConditionMatch.h"

#include <gtest/gtest.h>

#include <fstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

class MockSourceReader : public ISourceReader
{
   public:
    MockSourceReader() = delete;
    MockSourceReader(const std::string& filePath) : m_filePath(filePath) {}
    std::string readFile() const override
    {
        return scannerResponse;
    }

    std::string readFile(const std::string& filePath) const override
    {
        return scannerResponse;
    }

    void setScannerResonse(const std::string& response)
    {
        scannerResponse = response;
    };

   private:
    std::string m_filePath;
    std::string m_filecontent = "Some Mock Message";

    std::string scannerResponse =
        R"(// First Example only with text content that must be displayed in the source reader as comment)";
};

class ScannerForConditionMatchTest : public ::testing::Test
{
   protected:
    const std::string testURL =
        "https://github.com/HugorTorquato/MBA-TCC/tree/main/Implementation/src";
    const std::string testFilePath = "test.txt";
    const std::string testFileContent = "This is a test file content.";

    const std::string tempFolder = "/app/temp/";

    void SetUp() override {}

    void TearDown() override
    {
        fs::remove_all(tempFolder);
    }
};

// Tests

TEST_F(ScannerForConditionMatchTest, RetrieveFileContent)
{
    const json scannerExpectedResult = {
        {"main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/"
         "SimpleSorceExampleForReaderTests/main.cpp",
         "// First Example only with text content that must be displayed in the source reader as "
         "comment"}};
    const json downloadResult = {
        {"main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/"
         "SimpleSorceExampleForReaderTests/main.cpp",
         "Implementation/observability/source_code_for_testing/ProcessSourceFiles/"
         "SimpleSorceExampleForReaderTests/main.cpp"}};
    ScannerForConditionMatch scanner(downloadResult, [](const std::string& filePath)
                                     { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_EQ(actualResult, scannerExpectedResult);
}

TEST_F(ScannerForConditionMatchTest, EmptyDownloadResult)
{
    const json downloadResult = json::object();
    ScannerForConditionMatch scanner(downloadResult, [](const std::string& filePath)
                                     { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_TRUE(actualResult.empty());
}

TEST_F(ScannerForConditionMatchTest, SkipRootKey)
{
    const json downloadResult = {{"root", "some/path/to/root"},
                                 {"main.cpp", "some/path/to/main.cpp"}};
    ScannerForConditionMatch scanner(downloadResult, [](const std::string& filePath)
                                     { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_EQ(actualResult.size(), 1);
    EXPECT_TRUE(actualResult.contains("main.cpp"));
    EXPECT_FALSE(actualResult.contains("root"));
}

TEST_F(ScannerForConditionMatchTest, MultipleFiles)
{
    const json downloadResult = {{"file1.cpp", "path/to/file1.cpp"},
                                 {"file2.cpp", "path/to/file2.cpp"}};
    ScannerForConditionMatch scanner(downloadResult, [](const std::string& filePath)
                                     { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_EQ(actualResult.size(), 2);
    EXPECT_TRUE(actualResult.contains("file1.cpp"));
    EXPECT_TRUE(actualResult.contains("file2.cpp"));
}
