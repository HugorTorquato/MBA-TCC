#include "../../../src/ProcessSourceFiles/util/SourceReaderAsString.h"

#include <gtest/gtest.h>

#include <fstream>
#include <stdexcept>
#include <string>

class SourceReaderAsStringTest : public ::testing::Test
{
   protected:
    const std::string testFilePath = "test.txt";
    const std::string testFileContent = "This is a test file content.";
};

TEST_F(SourceReaderAsStringTest, ReadFileNotFound)
{
    SourceReaderAsString sourceReader;
    EXPECT_THROW(sourceReader.readFile("non_existent_file.txt"), std::runtime_error);
}

TEST_F(SourceReaderAsStringTest, ReadFileContent)
{
    // Create a test file with known content
    std::ofstream testFile(testFilePath);
    testFile << testFileContent;
    testFile.close();

    SourceReaderAsString sourceReader;
    std::string content = sourceReader.readFile(testFilePath);

    EXPECT_EQ(content, testFileContent);

    // Clean up the test file
    std::remove(testFilePath.c_str());
}

TEST_F(SourceReaderAsStringTest, ReadFileEmptyContent)
{
    // Create an empty test file
    std::ofstream testFile(testFilePath);
    testFile.close();

    SourceReaderAsString sourceReader;
    std::string content = sourceReader.readFile(testFilePath);

    EXPECT_EQ(content, "");

    // Clean up the test file
    std::remove(testFilePath.c_str());
}

TEST_F(SourceReaderAsStringTest, ReadFileWithSpecialCharacters)
{
    // Create a test file with special characters
    std::ofstream testFile(testFilePath);
    testFile << "Special characters: !@#$%^&*()_+";
    testFile.close();

    SourceReaderAsString sourceReader;
    std::string content = sourceReader.readFile(testFilePath);

    EXPECT_EQ(content, "Special characters: !@#$%^&*()_+");

    // Clean up the test file
    std::remove(testFilePath.c_str());
}

TEST_F(SourceReaderAsStringTest, ReadFileWithNewlineCharacters)
{
    // Create a test file with newline characters
    std::ofstream testFile(testFilePath);
    testFile << "Line 1\nLine 2\nLine 3";
    testFile.close();

    SourceReaderAsString sourceReader;
    std::string content = sourceReader.readFile(testFilePath);

    EXPECT_EQ(content, "Line 1\nLine 2\nLine 3");

    // Clean up the test file
    std::remove(testFilePath.c_str());
}