#include <gtest/gtest.h>
#include "../../../src/ProcessSourceFiles/ContainersInterface/ContainersInterface.h"

TEST(ContainersInterfaceTest, SingletonReturnsSameInstance)
{
    ContainersInterface& instance1 = ContainersInterface::getInstance();
    ContainersInterface& instance2 = ContainersInterface::getInstance();

    // Check that both references point to the same object
    EXPECT_EQ(&instance1, &instance2);
}

// You can also test its methods
TEST(ContainersInterfaceTest, SingletonMethodWorks)
{
    ContainersInterface& instance = ContainersInterface::getInstance();
    // instance.someMethod();
    // EXPECT_EQ(instance.someState(), expectedValue);
}