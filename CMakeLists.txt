cmake_minimum_required(VERSION 3.13)

set (CMAKE_CXX_STANDARD 17)
project(Saper)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(main main.cpp ${SOURCE_FILES})