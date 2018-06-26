cmake_minimum_required(VERSION 3.0)
project(ProteiTestTask)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(gtestMain ${CMAKE_CURRENT_SOURCE_DIR}/gtest_main.cpp)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(googletest)
add_subdirectory(network)
add_subdirectory(client)
add_subdirectory(server)
#add_subdirectory(integrationTests)


