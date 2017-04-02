set(SOURCE testbool.cpp)

#or, not both(will not complie)

#set(SOURCE test.cpp)

add_executable(runtest ${SOURCE})

target_link_libraries(runtest myvector)

target_link_libraries(runtest gtest gtest_main)