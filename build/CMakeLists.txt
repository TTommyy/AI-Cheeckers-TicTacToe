cmake_minimum_required(VERSION 3.0)
project(MyProject)

# Add the include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/checkers
    ${PROJECT_SOURCE_DIR}/alg
    ${PROJECT_SOURCE_DIR}/main
)

# Specify the source files for the executable
set(SOURCES main/main.cpp)

# Create the executable target
add_executable(MyExecutable ${SOURCES})

# Set the C++ standard
target_compile_features(MyExecutable PRIVATE cxx_std_20)