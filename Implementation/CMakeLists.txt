cmake_minimum_required(VERSION 3.10)
project(ApiServer)

set(CMAKE_CXX_STANDARD 20)

# Find Crow (Assuming it's installed)
find_package(Boost REQUIRED)
find_package(GTest REQUIRED)

# Include all .cpp source files from src/
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/src/*.h")
# Include the code under test here and all sources that it will test
file(GLOB_RECURSE TEST_SOURCES 
    "${CMAKE_SOURCE_DIR}/unitTests/*.cpp") # unit test definitions
file(GLOB_RECURSE TEST_SOURCES_TO_TEST  
    "${CMAKE_SOURCE_DIR}/src/Logger/*.cpp" # Logger source code under test
    "${CMAKE_SOURCE_DIR}/src/ProcessSourceFiles/*.cpp" # ProcessSourceFiles source code under test
    )

# Link Crow and Boost
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    include
    /include/Crow/include
)

# Build the API server
add_executable(api_server ${SOURCES})
target_link_libraries(api_server PRIVATE Boost::boost)
    # Faz o link do executável api_server com a biblioteca Boost. Aqui 
    # está usando o componente Boost::boost, que é apenas os headers. Se 
    # usar Boost com componentes binários (filesystem, system...), seria diferente.

# Build the unit tests
# add_executable(my_tests unitTests/my_test.cpp)
add_executable(my_tests ${TEST_SOURCES} ${TEST_SOURCES_TO_TEST})
target_link_libraries(my_tests PRIVATE GTest::gtest GTest::gmock GTest::gtest_main pthread)

    #Faz o link com:
    #GTest::gtest → Biblioteca principal do GTest
    #GTest::gmock → Biblioteca do Google Mock
    #GTest::gtest_main → Fornece o main() pronto
    #pthread → Threading POSIX necessário para o GTest funcionar corretamente
    #CURL_LIBRARIES -> using curl into the tests
#define a macro like UNIT_TEST only in your test target, and check it in code.
target_compile_definitions(my_tests PRIVATE UNIT_TEST)

# Add a custom target to format the code
add_custom_target(
    format
    COMMAND clang-format -i ${SOURCES} ${HEADERS} ${TEST_SOURCES}
    COMMENT "Formatting all C++ source and header files"
)

#-------------------------------------------------------------------------
# Dependency to download files from git
find_package(CURL REQUIRED)

# Include libcurl headers
include_directories(${CURL_INCLUDE_DIRS})

# For api_server, link libcurl
target_link_libraries(api_server PRIVATE ${CURL_LIBRARIES})
#-------------------------------------------------------------------------