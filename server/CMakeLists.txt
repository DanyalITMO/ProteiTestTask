cmake_minimum_required(VERSION 3.0)
project(server)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads)

set(SOURCES
        source/Helper.cpp
        source/main.cpp
        source/Statistic.cpp
        source/SyncOut.cpp include/SyncOut.h)
include_directories(include)

add_executable(server ${SOURCES})
target_link_libraries(server network ${CMAKE_THREAD_LIBS_INIT})