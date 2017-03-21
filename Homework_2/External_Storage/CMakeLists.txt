cmake_minimum_required(VERSION 3.6)
project(Array)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp )
add_executable(run ${SOURCE_FILES})

include_directories(array)

add_subdirectory(test)
add_subdirectory(array)

target_link_libraries(run myarray)
