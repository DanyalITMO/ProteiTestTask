cmake_minimum_required(VERSION 3.0)
project(server)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads)

set(SERVER_SOURCE
        source/ServerHelper.cpp
        source/SyncOut.cpp source/Setting.cpp
        CACHE INTERNAL ""
        )
include_directories(include)

add_executable(server ${SERVER_SOURCE} source/main.cpp)
target_link_libraries(server network ${CMAKE_THREAD_LIBS_INIT})