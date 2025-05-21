#include "../../../src/ProcessSourceFiles/util/SourceReaderAsString.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

// Test fixture for SourceReaderAsString
class SourceReaderAsStringTest : public ::testing::Test
{
   protected:
    const std::filesystem::path testFilePath = "/app/temp/test.txt";
    const std::string testFilePathName = "test.txt";
    const std::string testFileContent = "This is a test file content.";

    // Helper function to create a test file with specified content
    void createTestFile(const std::string& content)
    {
        std::filesystem::create_directories(testFilePath.parent_path());
        std::ofstream testFile(testFilePath);
        testFile << content;
        testFile.close();
    }

    // Helper function to clean up the test file
    void removeTestFile()
    {
        std::remove(testFilePath.c_str());
    }
};

// Tests

// Test for empty file path
TEST_F(SourceReaderAsStringTest, ReadFilePathEmpty)
{
    EXPECT_THROW(SourceReaderAsString sourceReader(""), std::invalid_argument);

    SourceReaderAsString sourceReader2(testFilePathName);
    EXPECT_THROW(sourceReader2.readFile(""), std::invalid_argument);
}

// Test for non-existent file
TEST_F(SourceReaderAsStringTest, ReadFileNotFound)
{
    SourceReaderAsString sourceReader(testFilePathName);
    EXPECT_THROW(sourceReader.readFile("non_existent_file.txt"), std::runtime_error);
}

// Test for reading file content
TEST_F(SourceReaderAsStringTest, ReadFileContent)
{
    createTestFile(testFileContent);

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, testFileContent);

    removeTestFile();
}

// Test for reading file content using constructor path
TEST_F(SourceReaderAsStringTest, ReadFileContentUsingConstructorPath)
{
    createTestFile(testFileContent);

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile();

    EXPECT_EQ(content, testFileContent);

    removeTestFile();
}

// Test for reading an empty file
TEST_F(SourceReaderAsStringTest, ReadFileEmptyContent)
{
    createTestFile("");

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, "");

    removeTestFile();
}

// Test for reading a file with special characters
TEST_F(SourceReaderAsStringTest, ReadFileWithSpecialCharacters)
{
    const std::string specialContent = "Special characters: !@#$%^&*()_+";
    createTestFile(specialContent);

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, specialContent);

    removeTestFile();
}

// Test for reading a file with newline characters
TEST_F(SourceReaderAsStringTest, ReadFileWithNewlineCharacters)
{
    const std::string multilineContent = "Line 1\nLine 2\nLine 3";
    createTestFile(multilineContent);

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, multilineContent);

    removeTestFile();
}

// New Test: Reading a file with very large content
TEST_F(SourceReaderAsStringTest, ReadFileWithLargeContent)
{
    const std::string largeContent(1000000, 'A');  // 1 million 'A' characters
    createTestFile(largeContent);

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, largeContent);

    removeTestFile();
}

// New Test: Reading a file with only whitespace
TEST_F(SourceReaderAsStringTest, ReadFileWithWhitespaceOnly)
{
    const std::string whitespaceContent = "    \n\t  ";
    createTestFile(whitespaceContent);

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, whitespaceContent);

    removeTestFile();
}
