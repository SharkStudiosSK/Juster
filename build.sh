#!/bin/bash

# Build script for Juster animation software
# This script automates the build process described in README.md

set -e  # Exit on any error

echo "Building Juster..."

# Function to check if a package is installed
check_dependency() {
    local package=$1
    local deb_package=$2
    
    if ! pkg-config --exists "$package" 2>/dev/null; then
        echo "❌ Missing dependency: $package"
        echo "   Install with: sudo apt install $deb_package"
        return 1
    else
        echo "✅ Found dependency: $package"
        return 0
    fi
}

# Check dependencies on Ubuntu/Debian systems
if command -v apt-get >/dev/null 2>&1; then
    echo "Checking dependencies..."
    
    deps_missing=false
    
    if ! check_dependency "sdl2" "libsdl2-dev"; then
        deps_missing=true
    fi
    
    if ! check_dependency "glew" "libglew-dev"; then
        deps_missing=true
    fi
    
    if $deps_missing; then
        echo ""
        echo "Missing dependencies detected. Install them with:"
        echo "sudo apt update && sudo apt install libsdl2-dev libglew-dev"
        echo ""
        read -p "Would you like to install dependencies now? (y/N): " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            sudo apt update && sudo apt install libsdl2-dev libglew-dev
        else
            echo "Please install dependencies manually and try again."
            exit 1
        fi
    fi
fi

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