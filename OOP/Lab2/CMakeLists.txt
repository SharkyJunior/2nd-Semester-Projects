cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect all .cpp files in the Source directory
file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/Source/*.cpp")

# Include the Source directory
file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/Source/*.hpp")

# Add the main file explicitly
set(MAIN_FILE "${CMAKE_SOURCE_DIR}/main.cpp")

# Create executable
add_executable(MyProject ${MAIN_FILE} ${SOURCE_FILES})
