cmake_minimum_required(VERSION 3.6)
project(Array)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Array.h ArrayPointer.h main.cpp Iterator.h Collection.h)
add_executable(Array ${SOURCE_FILES})