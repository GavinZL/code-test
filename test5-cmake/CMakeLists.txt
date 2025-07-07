cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME test5)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(ALL_FILES
    "test5-main.cpp"
)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test5-subcmake)

add_executable(${PROJECT_NAME} ${ALL_FILES})