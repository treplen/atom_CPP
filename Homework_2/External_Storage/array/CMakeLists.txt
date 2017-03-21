cmake_minimum_required(VERSION 3.6)
project(Array)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Array.h ArrayPointer.h Collection.h Iterator.h ArrayPointerBool.h Utils.h Utils.cpp)

add_library(myarray SHARED ${SOURCE_FILES})