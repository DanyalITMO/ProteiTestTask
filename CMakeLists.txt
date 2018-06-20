cmake_minimum_required(VERSION 3.0)
project(ProteiTestTask)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
add_subdirectory(network)
add_subdirectory(client)
add_subdirectory(server)


