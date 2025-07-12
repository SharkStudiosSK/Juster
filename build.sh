#!/bin/bash

# Build script for Juster animation software
# This script automates the build process described in README.md

set -e  # Exit on any error

echo "Building Juster..."

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# Navigate to build directory
cd build

# Configure the project
echo "Configuring with CMake..."
cmake ..

# Build the project
echo "Building..."
cmake --build .

echo "Build completed successfully!"
echo "Executable location: build/bin/Juster"