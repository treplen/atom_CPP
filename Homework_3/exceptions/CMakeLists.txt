cmake_minimum_required(VERSION 3.6)
project(exceptions)

set(CMAKE_CXX_STANDARD 11)

link_libraries(gtest)

set(SOURCE_FILES main.cpp good_exception.h good_exception.cpp)
add_executable(exceptions ${SOURCE_FILES})