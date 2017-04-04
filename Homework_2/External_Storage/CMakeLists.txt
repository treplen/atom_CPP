cmake_minimum_required(VERSION 3.6)
project(Vector)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp )
add_executable(run ${SOURCE_FILES})

include_directories(vector)

add_subdirectory(test)
add_subdirectory(vector)

target_link_libraries(run myvector)
