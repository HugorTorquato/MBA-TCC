#!/bin/bash

# echo "<> Cleaning and setting up build directory..."
# rm -rf ../build
# mkdir ../build
# cd ../build

# # echo "<> Running CMake..."
# # cmake ..

# echo "<> Use ASAN (AddressSanitizer) to catch the exact location:..."
# cmake -DCMAKE_CXX_FLAGS="-fsanitize=address -g" ..

# echo "<> Running Auto-format..."
# make format

# echo "<> Building project..."
# make -j$(nproc)

# echo "<> Build finished."

# echo "<> Running unit tests..."
# ./my_tests




BUILD_DIR="../build"

if [[ "$1" == "--full" ]]; then
    echo "<> Performing full clean build..."
    rm -rf $BUILD_DIR
    mkdir -p $BUILD_DIR
else
    echo "<> Performing incremental build..."
    mkdir -p $BUILD_DIR
fi

cd $BUILD_DIR || exit 1

# Only rerun CMake if no Makefiles yet
if [ ! -f Makefile ]; then
    echo "<> Running CMake..."
    cmake -DCMAKE_CXX_FLAGS="-fsanitize=address -g" ..
fi

echo "<> Running Auto-format..."
make format

echo "<> Building project..."
make -j$(nproc)

echo "<> Build finished."

echo "<> Running unit tests..."
./my_tests


# echo "<> Starting the API..."
# pkill api_server
# ./api_server

