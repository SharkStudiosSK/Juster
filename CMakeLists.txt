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
pkg_check_modules(SDL2 REQUIRED sdl2)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

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