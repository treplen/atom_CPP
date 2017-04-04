cmake_minimum_required(VERSION 3.6)
project(Utils)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES utils.cpp utils.h)
add_library(utils ${SOURCE_FILES})
