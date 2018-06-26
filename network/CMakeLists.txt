cmake_minimum_required(VERSION 3.0)
project(network)

set(CMAKE_CXX_STANDARD 17)

set(NETWORK_SOURCE
        source/TCPServer.cpp
        source/TCPSession.cpp
        source/Server.cpp
        source/Client.cpp
        source/NetworkHelper.cpp
        include/Server.h
        source/UDPServer.cpp
        include/UDPServer.h
        source/UDPIncomingMessage.cpp
        include/UDPIncomingMessage.h
        source/UDPClient.cpp
        include/UDPClient.h
        source/TCPClient.cpp
        include/TCPClient.h
        source/ApplicationProtocol.cpp
        source/HighLevelSocket.cpp
        CACHE INTERNAL ""
        )

include_directories(include)
add_library(${PROJECT_NAME} SHARED ${NETWORK_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

set(TEST_SOURCES
        tests/ApplicationProtocolTester.cpp
        ${gtestMain}
        )

add_executable(${PROJECT_NAME}.Tester ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}.Tester ${PROJECT_NAME} gtest)