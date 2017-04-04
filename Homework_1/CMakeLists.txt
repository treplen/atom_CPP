cmake_minimum_required(VERSION 3.6)
project(Stack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Test.cpp Stack.h )
link_libraries(gtest)
add_executable(Stack ${SOURCE_FILES})