#include "../../../src/ProcessSourceFiles/util/LineFile.h"

#include <gtest/gtest.h>

class LineFileTest : public ::testing::Test
{
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(LineFileTest, GettersReturnCorrectValues)
{
    LineFile lineFile(1, 2, 3, 4);

    EXPECT_EQ(lineFile.getLine(), 1);
    EXPECT_EQ(lineFile.getCol(), 2);
    EXPECT_EQ(lineFile.getEndLine(), 3);
    EXPECT_EQ(lineFile.getEndCol(), 4);
}

TEST_F(LineFileTest, getLineFileAsStringReturnsCorrectString)
{
    LineFile lineFile(1, 2, 3, 4);

    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: 1, Col: 2, End Line: 3, End Col: 4");
}

TEST_F(LineFileTest, getLineFileAsStringWithNegativeValues)
{
    LineFile lineFile(-1, -2, -3, -4);

    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: -1, Col: -2, End Line: -3, End Col: -4");
}

TEST_F(LineFileTest, getLineFileAsStringWithZeroValues)
{
    LineFile lineFile(0, 0, 0, 0);

    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: 0, Col: 0, End Line: 0, End Col: 0");
}

TEST_F(LineFileTest, getLineFileAsStringWithMixedValues)
{
    LineFile lineFile(1, 0, -1, 4);

    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: 1, Col: 0, End Line: -1, End Col: 4");
}

TEST_F(LineFileTest, DefaultConstructor)
{
    LineFile lineFile;

    EXPECT_EQ(lineFile.getLine(), 0);
    EXPECT_EQ(lineFile.getCol(), 0);
    EXPECT_EQ(lineFile.getEndLine(), 0);
    EXPECT_EQ(lineFile.getEndCol(), 0);
    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: 0, Col: 0, End Line: 0, End Col: 0");
}

TEST_F(LineFileTest, SettersUpdateValues)
{
    LineFile lineFile;

    lineFile.setLine(1);
    lineFile.setCol(2);
    lineFile.setEndLine(3);
    lineFile.setEndCol(4);

    EXPECT_EQ(lineFile.getLine(), 1);
    EXPECT_EQ(lineFile.getCol(), 2);
    EXPECT_EQ(lineFile.getEndLine(), 3);
    EXPECT_EQ(lineFile.getEndCol(), 4);
}

TEST_F(LineFileTest, SettersWithNegativeValues)
{
    LineFile lineFile;

    lineFile.setLine(-1);
    lineFile.setCol(-2);
    lineFile.setEndLine(-3);
    lineFile.setEndCol(-4);

    EXPECT_EQ(lineFile.getLine(), -1);
    EXPECT_EQ(lineFile.getCol(), -2);
    EXPECT_EQ(lineFile.getEndLine(), -3);
    EXPECT_EQ(lineFile.getEndCol(), -4);
}

TEST_F(LineFileTest, SettersWithZeroValues)
{
    LineFile lineFile;

    lineFile.setLine(0);
    lineFile.setCol(0);
    lineFile.setEndLine(0);
    lineFile.setEndCol(0);

    EXPECT_EQ(lineFile.getLine(), 0);
    EXPECT_EQ(lineFile.getCol(), 0);
    EXPECT_EQ(lineFile.getEndLine(), 0);
    EXPECT_EQ(lineFile.getEndCol(), 0);
}

TEST_F(LineFileTest, SettersWithFileName)
{
    LineFile lineFile(1, 2, 3, 4, "test_file.cpp");

    EXPECT_EQ(lineFile.getLine(), 1);
    EXPECT_EQ(lineFile.getCol(), 2);
    EXPECT_EQ(lineFile.getEndLine(), 3);
    EXPECT_EQ(lineFile.getEndCol(), 4);
    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: 1, Col: 2, End Line: 3, End Col: 4 with file name: test_file.cpp");
}

TEST_F(LineFileTest, SetFileName)
{
    LineFile lineFile;
    lineFile.setFileName("test_file.cpp");

    EXPECT_EQ(lineFile.getFileName(), "test_file.cpp");
    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: 0, Col: 0, End Line: 0, End Col: 0 with file name: test_file.cpp");
}

TEST_F(LineFileTest, EmptyFileName)
{
    LineFile lineFile(1, 2, 3, 4, "");

    EXPECT_EQ(lineFile.getLine(), 1);
    EXPECT_EQ(lineFile.getCol(), 2);
    EXPECT_EQ(lineFile.getEndLine(), 3);
    EXPECT_EQ(lineFile.getEndCol(), 4);
    EXPECT_EQ(lineFile.getLineFileAsString(),
              "[LineFile] Line: 1, Col: 2, End Line: 3, End Col: 4");
}
