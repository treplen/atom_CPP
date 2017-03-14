include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE testbool.cpp)

#or, not both(will not complie)

#set(SOURCE test.cpp)

add_executable(runtest ${SOURCE})

target_link_libraries(runtest myarray)

target_link_libraries(runtest gtest gtest_main)