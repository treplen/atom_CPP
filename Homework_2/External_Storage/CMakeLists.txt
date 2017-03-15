cmake_minimum_required(VERSION 3.6)
project(Array)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Array.h ArrayPointer.h Iterator.h Collection.h Utils.h Test.cpp Utils.cpp)
link_libraries(gtest)
add_executable(Array ${SOURCE_FILES})