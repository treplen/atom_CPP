cmake_minimum_required(VERSION 3.6)
project(Vector)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Vector.h VectorPointer.h Collection.h Iterator.h VectorPointerBool.h Utils.h Utils.cpp bit_pointer.h)

add_library(myvector SHARED ${SOURCE_FILES})