#include "../src/Logger/Log.h"

#include <gtest/gtest.h>

#include <fstream>
#include <string>

namespace
{
std::string readFile(const std::string& path)
{
    std::ifstream file(path);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
}  // namespace

class LoggerTest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        std::remove(m_logPath.c_str());
    }

    void TearDown() override
    {
        std::remove(m_logPath.c_str());
    }

   protected:
    static const std::string m_logPath;
};

const std::string LoggerTest::m_logPath = "../build/app.log";

TEST_F(LoggerTest, VerifyIfLogFileExists)
{
    Logger::getInstance().log("VerifyIfLogFileExists Test");
    std::ifstream file(LoggerTest::m_logPath);
    EXPECT_TRUE(file.good());
}

TEST_F(LoggerTest, VerifyIfLogFileDonNotExists)
{
    // auto& logger = Logger::getInstance();
    std::ifstream file(LoggerTest::m_logPath);
    EXPECT_FALSE(file.good());
}

TEST_F(LoggerTest, VerifyMessageWrittenToLogs)
{
    const std::string message = "VerifyMessageWrittenToLogs Test";
    Logger::getInstance().log(message);
    EXPECT_EQ(readFile(LoggerTest::m_logPath), message + "\n");
}

TEST_F(LoggerTest, VerifyThatNoLogIsWrittenIfDisabledThe_EnabledLogs_Flag)
{
    const std::string message = "VerifyThatNoLogIsWrittenIfDisabledThe_EnabledLogs_Flag Test";
    auto& logger = Logger::getInstance();

    // Logs are enabled by default
    EXPECT_TRUE(logger.getEnabledLogs());

    logger.setEnabledLogs(false);
    logger.log(message);

    EXPECT_EQ(readFile(LoggerTest::m_logPath), "");
}