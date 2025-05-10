#include "../../src/utils/inlineFreeFunctions.h"
// #include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>  // Required for std::ofstream

TEST(FilesystemUtilsTest, DeleteTempFolder_RemovesExistingFolder)
{
    const std::filesystem::path tempFolder = "/app/test_temp_folder";

    // Create folder and dummy file
    std::filesystem::create_directory(tempFolder);
    std::ofstream(tempFolder / "dummy.txt") << "test";

    ASSERT_TRUE(std::filesystem::exists(tempFolder));
    inlineFreeFunctions::deleteTempFolder(tempFolder);
    EXPECT_FALSE(std::filesystem::exists(tempFolder));
}