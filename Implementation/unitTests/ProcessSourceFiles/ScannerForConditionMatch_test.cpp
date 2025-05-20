#include "../../src/ProcessSourceFiles/ScannerForConditionMatch.h"

#include <gtest/gtest.h>

#include <fstream>
#include <stdexcept>
#include <string>

#include "../../src/ProcessSourceFiles/util/SourceReaderAsString.h"

class ScannerForConditionMatchTest : public ::testing::Test
{
   protected:
    const std::string testFilePath = "test.txt";
    const std::string testFileContent = "This is a test file content.";
};

// Tests

TEST_F(ScannerForConditionMatchTest, RetrieveFileContent)
{
    // Create a test file with known content
    std::ofstream testFile(testFilePath);
    testFile << testFileContent;
    testFile.close();

    ScannerForConditionMatch scanner;
    std::string content = scanner.retrieveSourceFileContent(SourceReaderAsString(testFilePath));

    EXPECT_EQ(content, testFileContent);

    std::remove(testFilePath.c_str());
}