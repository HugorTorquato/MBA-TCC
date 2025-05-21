#include "../../../src/ProcessSourceFiles/util/SourceReaderAsString.h"

#include <gtest/gtest.h>

#include <fstream>
#include <stdexcept>
#include <string>

// TODO: Ask copilot to create more tests and refactor this

class SourceReaderAsStringTest : public ::testing::Test
{
   protected:
    const std::filesystem::path testFilePath = "/app/temp/test.txt";
    const std::string testFilePathName = "test.txt";
    const std::string testFileContent = "This is a test file content.";
};

// Tests

TEST_F(SourceReaderAsStringTest, ReadFilePathEmpty)
{
    EXPECT_THROW(SourceReaderAsString sourceReader(""), std::invalid_argument);

    SourceReaderAsString sourceReader2(testFilePathName);
    EXPECT_THROW(sourceReader2.readFile(""), std::invalid_argument);
}

TEST_F(SourceReaderAsStringTest, ReadFileNotFound)
{
    SourceReaderAsString sourceReader(testFilePathName);
    EXPECT_THROW(sourceReader.readFile("non_existent_file.txt"), std::runtime_error);
}

TEST_F(SourceReaderAsStringTest, ReadFileContent)
{
    // Create a test file with known content
    std::cout << "[ReadFileContent TESTS ] testFilePath: " << testFilePath << std::endl;
    std::filesystem::create_directories(testFilePath.parent_path());
    std::ofstream testFile(testFilePath);
    testFile << testFileContent;
    testFile.close();

    EXPECT_TRUE(std::filesystem::exists(testFilePath));

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, testFileContent);

    // Clean up the test file
    std::remove(testFilePath.c_str());
}

TEST_F(SourceReaderAsStringTest, ReadFileContentUsingConstructorPath)
{
    // Create a test file with known content
    std::filesystem::create_directories(testFilePath.parent_path());
    std::ofstream testFile(testFilePath);
    testFile << testFileContent;
    testFile.close();

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile();

    EXPECT_EQ(content, testFileContent);

    // Clean up the test file
    std::remove(testFilePath.c_str());
}

TEST_F(SourceReaderAsStringTest, ReadFileEmptyContent)
{
    // Create an empty test file
    std::filesystem::create_directories(testFilePath.parent_path());
    std::ofstream testFile(testFilePath);
    testFile.close();

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, "");

    // Clean up the test file
    std::remove(testFilePath.c_str());
}

TEST_F(SourceReaderAsStringTest, ReadFileWithSpecialCharacters)
{
    // Create a test file with special characters
    std::filesystem::create_directories(testFilePath.parent_path());
    std::ofstream testFile(testFilePath);
    testFile << "Special characters: !@#$%^&*()_+";
    testFile.close();

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, "Special characters: !@#$%^&*()_+");

    // Clean up the test file
    std::remove(testFilePath.c_str());
}

TEST_F(SourceReaderAsStringTest, ReadFileWithNewlineCharacters)
{
    // Create a test file with newline characters
    std::filesystem::create_directories(testFilePath.parent_path());
    std::ofstream testFile(testFilePath);
    testFile << "Line 1\nLine 2\nLine 3";
    testFile.close();

    SourceReaderAsString sourceReader(testFilePathName);
    std::string content = sourceReader.readFile(testFilePathName);

    EXPECT_EQ(content, "Line 1\nLine 2\nLine 3");

    // Clean up the test file
    std::remove(testFilePath.c_str());
}
