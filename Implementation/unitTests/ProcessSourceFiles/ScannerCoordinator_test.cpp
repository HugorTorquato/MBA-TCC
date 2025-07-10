#include "../../src/ProcessSourceFiles/ScannerCoordinator.h"

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

class ScannerCoordinatorTest : public ::testing::Test
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

TEST_F(ScannerCoordinatorTest, RetrieveFileContent)
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
    ScannerCoordinator scanner(downloadResult, [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_EQ(actualResult, scannerExpectedResult);
}

TEST_F(ScannerCoordinatorTest, EmptyDownloadResult)
{
    const json downloadResult = json::object();
    ScannerCoordinator scanner(downloadResult, [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_TRUE(actualResult.empty());
}

TEST_F(ScannerCoordinatorTest, SkipRootKey)
{
    const json downloadResult = {{"root", "some/path/to/root"},
                                 {"main.cpp", "some/path/to/main.cpp"}};
    ScannerCoordinator scanner(downloadResult, [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_EQ(actualResult.size(), 1);
    EXPECT_TRUE(actualResult.contains("main.cpp"));
    EXPECT_FALSE(actualResult.contains("root"));
}

TEST_F(ScannerCoordinatorTest, MultipleFiles)
{
    const json downloadResult = {{"file1.cpp", "path/to/file1.cpp"},
                                 {"file2.cpp", "path/to/file2.cpp"}};
    ScannerCoordinator scanner(downloadResult, [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    const auto actualResult = scanner.downloadAndRetrieveSourceFileContent(testURL);

    EXPECT_EQ(actualResult.size(), 2);
    EXPECT_TRUE(actualResult.contains("file1.cpp"));
    EXPECT_TRUE(actualResult.contains("file2.cpp"));
}

TEST_F(ScannerCoordinatorTest, evaluateFromJsonResponse)
{
    const json downloadResult = {{"file1.cpp", "path/to/file1.cpp"},
                                 {"file2.cpp", "path/to/file2.cpp"}};

    // const std::string jsonResponse =
    //     R"({classDef.h:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/classDef.h:
    //     #pragma once\n\nclass hugo {\n\n};,
    //     main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/main.cpp:
    //     #include \"classDef.h\"})";

    // Now jsonResponse is a real nlohmann::json object, and your loop with content.items() will
    // correctly iterate through each key–value pair.
    json jsonResponse = {{"classDef.h:Implementation/observability/source_code_for_testing/"
                          "ProcessSourceFiles/TwoFileSourceCode/classDef.h",
                          "#pragma once\n\nclass hugo {\n\n};"},
                         {"main.cpp:Implementation/observability/source_code_for_testing/"
                          "ProcessSourceFiles/TwoFileSourceCode/main.cpp",
                          "#include \"classDef.h\""}};

    ScannerCoordinator scanner(downloadResult, [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    EXPECT_EQ(file_contents.size(), 2);
    EXPECT_EQ(file_contents[0].first,
              "classDef.h:Implementation/observability/source_code_for_testing/"
              "ProcessSourceFiles/TwoFileSourceCode/classDef.h");
    EXPECT_EQ(file_contents[0].second, "#pragma once\n\nclass hugo {\n\n};");
    EXPECT_EQ(file_contents[1].first,
              "main.cpp:Implementation/observability/source_code_for_testing/"
              "ProcessSourceFiles/TwoFileSourceCode/main.cpp");
    EXPECT_EQ(file_contents[1].second, "#include \"classDef.h\"");
}

TEST_F(ScannerCoordinatorTest, returnEmptyForEmptyJson)
{
    const json downloadResult = json::object();
    ScannerCoordinator scanner(downloadResult, [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(json::object());

    EXPECT_TRUE(file_contents.empty());
}

TEST_F(ScannerCoordinatorTest, evaluateJsonContent_SingleEntry)
{
    json jsonResponse = {{"file.cpp:path/to/file.cpp", "int main() { return 0; }"}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    ASSERT_EQ(file_contents.size(), 1);
    EXPECT_EQ(file_contents[0].first, "file.cpp:path/to/file.cpp");
    EXPECT_EQ(file_contents[0].second, "int main() { return 0; }");
}

TEST_F(ScannerCoordinatorTest, evaluateJsonContent_MultipleEntries)
{
    json jsonResponse = {
        {"a.cpp:path/a.cpp", "a"}, {"b.cpp:path/b.cpp", "b"}, {"c.cpp:path/c.cpp", "c"}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    ASSERT_EQ(file_contents.size(), 3);
    EXPECT_EQ(file_contents[0].second, "a");
    EXPECT_EQ(file_contents[1].second, "b");
    EXPECT_EQ(file_contents[2].second, "c");
}

TEST_F(ScannerCoordinatorTest, evaluateJsonContent_NonStringValue)
{
    json jsonResponse = {{"file.cpp:path/to/file.cpp", 12345}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    ASSERT_EQ(file_contents.size(), 1);
    EXPECT_EQ(file_contents[0].first, "file.cpp:path/to/file.cpp");
    // Should convert non-string to string via json::dump or similar
    EXPECT_EQ(file_contents[0].second, "12345.000000");
}

TEST_F(ScannerCoordinatorTest, evaluateJsonContent_NestedObjectValue)
{
    json jsonResponse = {{"file.cpp:path/to/file.cpp", {{"key", "value"}}}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    ASSERT_EQ(file_contents.size(), 1);
    EXPECT_EQ(file_contents[0].first, "file.cpp:path/to/file.cpp");
    // Should convert object to string (e.g., {"key":"value"})
    EXPECT_EQ(file_contents[0].second, "{\"key\":\"value\"}");
}

TEST_F(ScannerCoordinatorTest, evaluateJsonContent_NullValue)
{
    json jsonResponse = {{"file.cpp:path/to/file.cpp", nullptr}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    ASSERT_EQ(file_contents.size(), 1);
    EXPECT_EQ(file_contents[0].first, "file.cpp:path/to/file.cpp");
    EXPECT_EQ(file_contents[0].second, "null");
}

TEST_F(ScannerCoordinatorTest, evaluateJsonContent_EmptyStringValue)
{
    json jsonResponse = {{"file.cpp:path/to/file.cpp", ""}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    ASSERT_EQ(file_contents.size(), 1);
    EXPECT_EQ(file_contents[0].first, "file.cpp:path/to/file.cpp");
    EXPECT_EQ(file_contents[0].second, "");
}

TEST_F(ScannerCoordinatorTest, evaluateJsonContent_SpecialCharacters)
{
    json jsonResponse = {{"fïlè.cpp:päth/ƒïlè.cpp", "lïñé1\nlïñé2\t\u2603"}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    ASSERT_EQ(file_contents.size(), 1);
    EXPECT_EQ(file_contents[0].first, "fïlè.cpp:päth/ƒïlè.cpp");
    EXPECT_EQ(file_contents[0].second, "lïñé1\nlïñé2\t\u2603");
}

////////////////////////////////////////

TEST_F(ScannerCoordinatorTest, evaluateGroupTokensByFile_SingleEntry)
{
    json jsonResponse = {{"file.cpp:path/to/file.cpp", "int main() { return 0; }"}};
    ScannerCoordinator scanner(json::object(), [](const std::string& filePath)
                               { return std::make_unique<MockSourceReader>(filePath); });

    auto file_contents = scanner.evaluateJsonContent(jsonResponse);

    scanner.groupTokensByFile(file_contents);
}