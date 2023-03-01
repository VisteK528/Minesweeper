cmake_minimum_required(VERSION 3.13)
project(Saper)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(main ${SOURCE_FILES})