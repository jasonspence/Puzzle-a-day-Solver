cmake_minimum_required(VERSION 3.16)

# Set the project name and specify C++ 23 standard
project(Solver LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set debug mode
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Specify the compiler
set(CMAKE_CXX_COMPILER "g++")

# Add the executable
add_executable(Solver main.cpp)

# Set the output directory for executables
set_target_properties(Solver PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
