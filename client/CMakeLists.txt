cmake_minimum_required(VERSION 3.0)
project(client)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(CLIENT_SOURCES
        source/ClientHelper.cpp
        source/Settings.cpp
        CACHE INTERNAL ""
        )

message("client" ${CLIENT_SOURCES})
add_executable(${PROJECT_NAME} ${CLIENT_SOURCES} source/main.cpp)

set(TesterName ${PROJECT_NAME}.Tester)
target_link_libraries(${PROJECT_NAME} network)

set(TEST_CLIENT_SOURCES
        ${CLIENT_SOURCES}
        tests/ClientTester.cpp
        tests/SettingTester.cpp
        ${gtestMain}
        )
add_executable(${TesterName} ${TEST_CLIENT_SOURCES})
target_link_libraries(${TesterName}  gtest network)
