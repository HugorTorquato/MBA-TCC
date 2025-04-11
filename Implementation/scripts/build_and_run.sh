#!/bin/bash

echo "----> Cleaning and setting up build directory..."
rm -rf ../build
mkdir ../build
cd ../build

echo "----> Running CMake..."
cmake ..

echo "----> Building project..."
make -j$(nproc)

echo "----> Build finished."

#echo "----> Running unit tests..."
#./my_tests

echo "----> Starting the API..."
pkill api_server
./api_server