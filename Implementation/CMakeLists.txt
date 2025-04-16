cmake_minimum_required(VERSION 3.10)
project(ApiServer)

set(CMAKE_CXX_STANDARD 20)

# Find Crow (Assuming it's installed)
find_package(Boost REQUIRED)
find_package(GTest REQUIRED)

# Include all .cpp source files from src/
file(GLOB_RECURSE SOURCES "src/*.cpp")
# Include the code under test here and all sources that it will test
file(GLOB_RECURSE TEST_SOURCES 
    "unitTests/*.cpp" # unit test definitions
    "src/Logger/*.cpp" # Logger source code under test
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
add_executable(my_tests ${TEST_SOURCES})
target_link_libraries(my_tests PRIVATE GTest::gtest GTest::gmock GTest::gtest_main pthread)
    #Faz o link com:
    #GTest::gtest → Biblioteca principal do GTest
    #GTest::gmock → Biblioteca do Google Mock
    #GTest::gtest_main → Fornece o main() pronto
    #pthread → Threading POSIX necessário para o GTest funcionar corretamente

