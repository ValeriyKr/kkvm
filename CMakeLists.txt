cmake_minimum_required(VERSION 3.3)
project(kkvm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -O2")

include_directories("include")

set(SOURCE_FILES src/main.cpp src/kkvm.cpp src/instructionSet.cpp)

add_executable(kkvm ${SOURCE_FILES})
