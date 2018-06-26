cmake_minimum_required(VERSION 3.0)
project(integrationTests)

set(CMAKE_CXX_STANDARD 17)

set(INTEGRATE_SOURCE
    source/IntTests.cpp
)
message("integreate" ${CLIENT_SOURCES})
add_executable(${PROJECT_NAME} ${INTEGRATE_SOURCE} ${CLIENT_SOURCE} ${SERVER_SOURCE} ${gtestMain})
target_link_libraries(${PROJECT_NAME} network gtest)
