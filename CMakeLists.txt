cmake_minimum_required(VERSION 3.15)

# Project Information
project(Juster 
    VERSION 0.1.0
    DESCRIPTION "Free, Open Source Animation Software"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# Check for SDL2
pkg_check_modules(SDL2 sdl2)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR 
        "SDL2 not found! Please install the SDL2 development package:\n"
        "  Ubuntu/Debian: sudo apt install libsdl2-dev\n"
        "  Fedora/CentOS: sudo dnf install SDL2-devel\n"
        "  macOS: brew install sdl2\n"
        "  Windows: Download from https://libsdl.org/")
endif()

# Check for OpenGL
find_package(OpenGL REQUIRED)

# Check for GLEW
find_package(GLEW)
if(NOT GLEW_FOUND)
    message(FATAL_ERROR 
        "GLEW not found! Please install the GLEW development package:\n"
        "  Ubuntu/Debian: sudo apt install libglew-dev\n"
        "  Fedora/CentOS: sudo dnf install glew-devel\n"
        "  macOS: brew install glew\n"
        "  Windows: Download from http://glew.sourceforge.net/")
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/Renderer.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${SDL2_CFLAGS_OTHER})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)