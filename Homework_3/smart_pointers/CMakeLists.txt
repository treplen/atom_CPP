cmake_minimum_required(VERSION 3.6)
project(Homework_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES smart_pointer.h Utils.h unique_ptr.h auto_ptr.h shared_ptr.h tests.cpp)
link_libraries(gtest)
add_executable(Homework_3 ${SOURCE_FILES})