cmake_minimum_required(VERSION 3.6)
project(Interpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp VCPU.cpp VCPU.h)
add_executable(Interpreter ${SOURCE_FILES})