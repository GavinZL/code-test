cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME test3)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(ALL_FILES
    "test3-classA.h"
    "test3-share_ptr.cpp"
    "test3-main.cpp"
)

add_executable(${PROJECT_NAME} ${ALL_FILES})