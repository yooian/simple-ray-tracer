# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

project(simple-ray-tracer)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the executable
add_executable(simple-ray-tracer main.cc)
