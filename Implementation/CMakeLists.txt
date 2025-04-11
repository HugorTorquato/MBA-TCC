cmake_minimum_required(VERSION 3.10)
project(ApiServer)

set(CMAKE_CXX_STANDARD 20)

# Find Crow (Assuming it's installed)
find_package(Boost REQUIRED)

add_executable(api_server src/main.cpp)

# Link Crow and Boost
include_directories(/Crow/include)
target_link_libraries(api_server PRIVATE Boost::boost)

find_package(GTest REQUIRED)

add_executable(my_tests unitTests/my_test.cpp)
target_link_libraries(my_tests GTest::gtest GTest::gmock GTest::gtest_main pthread)
