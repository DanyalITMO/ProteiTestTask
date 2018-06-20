cmake_minimum_required(VERSION 3.0)
project(client)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
        source/ClientHelper.cpp
        source/Settings.cpp
        )
add_executable(${PROJECT_NAME} source/main.cpp)

set(TesterName ${PROJECT_NAME}.Tester)
add_executable(${TesterName} tests/ClientTester.cpp ${gtestMain})
target_link_libraries(${TesterName} #[[gtest_main]] gtest)
target_link_libraries(client network)