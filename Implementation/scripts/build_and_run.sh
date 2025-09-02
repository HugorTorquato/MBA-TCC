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
SANITIZER=""

# Parse options
while [[ $# -gt 0 ]]; do
    case "$1" in
        --full)
            FULL_BUILD=1
            ;;
        --asan)
            SANITIZER="address"
            ;;
        --tsan)
            SANITIZER="thread"
            ;;
        --ubsan)
            SANITIZER="undefined"
            ;;
        --msan)
            SANITIZER="memory"
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
    shift
done

if [[ "$FULL_BUILD" == "1" ]]; then
    echo "<> Performing full clean build..."
    rm -rf $BUILD_DIR
    mkdir -p $BUILD_DIR
else
    echo "<> Performing incremental build..."
    mkdir -p $BUILD_DIR
fi

cd $BUILD_DIR || exit 1

# Set sanitizer flags if specified
if [[ -n "$SANITIZER" ]]; then
    SAN_FLAGS="-fsanitize=$SANITIZER -g"
    echo "<> Using $SANITIZER sanitizer..."
else
    SAN_FLAGS="-g"
fi

# Only rerun CMake if no Makefiles yet
if [ ! -f Makefile ]; then
    echo "<> Running CMake..."
    cmake -DCMAKE_CXX_FLAGS="$SAN_FLAGS" ..
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

