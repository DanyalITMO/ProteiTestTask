cmake_minimum_required(VERSION 3.0)
project(client)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
        source/ClientHelper.cpp
        source/Settings.cpp
        )
add_executable(${PROJECT_NAME} ${SOURCES} source/main.cpp)

set(TesterName ${PROJECT_NAME}.Tester)
target_link_libraries(${PROJECT_NAME} network)


set(TEST_SOURCES
        ${SOURCES}
        tests/ClientTester.cpp
        tests/SettingTester.cpp
        ${gtestMain}
        )
add_executable(${TesterName} ${TEST_SOURCES})
target_link_libraries(${TesterName} #[[gtest_main]] gtest network)
