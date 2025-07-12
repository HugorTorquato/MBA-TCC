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

TEST_F(LineFileTest, LogLineFileReturnsCorrectString)
{
    LineFile lineFile(1, 2, 3, 4);

    EXPECT_EQ(lineFile.logLineFile(), "[LineFile] Line: 1, Col: 2, End Line: 3, End Col: 4");
}

TEST_F(LineFileTest, LogLineFileWithNegativeValues)
{
    LineFile lineFile(-1, -2, -3, -4);

    EXPECT_EQ(lineFile.logLineFile(), "[LineFile] Line: -1, Col: -2, End Line: -3, End Col: -4");
}

TEST_F(LineFileTest, LogLineFileWithZeroValues)
{
    LineFile lineFile(0, 0, 0, 0);

    EXPECT_EQ(lineFile.logLineFile(), "[LineFile] Line: 0, Col: 0, End Line: 0, End Col: 0");
}

TEST_F(LineFileTest, LogLineFileWithMixedValues)
{
    LineFile lineFile(1, 0, -1, 4);

    EXPECT_EQ(lineFile.logLineFile(), "[LineFile] Line: 1, Col: 0, End Line: -1, End Col: 4");
}
