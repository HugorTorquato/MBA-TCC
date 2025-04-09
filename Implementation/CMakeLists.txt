cmake_minimum_required(VERSION 3.10)
project(ApiServer)

set(CMAKE_CXX_STANDARD 20)

# Find Crow (Assuming it's installed)
find_package(Boost REQUIRED)

add_executable(api_server src/main.cpp)

# Link Crow and Boost
include_directories(/Crow/include)
target_link_libraries(api_server PRIVATE Boost::boost)