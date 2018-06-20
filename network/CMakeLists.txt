cmake_minimum_required(VERSION 3.0)
project(network)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
        source/TCPServer.cpp
        source/TCPSession.cpp
        source/Server.cpp
        source/Client.cpp
        source/Helper.cpp
        include/Server.h
        source/UDPServer.cpp
        include/UDPServer.h
        source/UDPIncomingMessage.cpp
        include/UDPIncomingMessage.h
        source/UDPClient.cpp
        include/UDPClient.h
        source/TCPClient.cpp
        include/TCPClient.h)

include_directories(include)
add_library(network SHARED ${SOURCE})
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )