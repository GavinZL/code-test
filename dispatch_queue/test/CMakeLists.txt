cmake_minimum_required(VERSION 3.14)

# 设置GoogleTest选项
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 下载并构建GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

# 设置GoogleTest选项
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 使GoogleTest可用
FetchContent_MakeAvailable(googletest)

# 启用测试
enable_testing()

# 设置测试可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加测试源文件
file(GLOB TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# 创建测试可执行文件
add_executable(dispatch_queue_test ${TEST_SOURCES})

# 设置测试目标的属性
set_target_properties(dispatch_queue_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# 包含头文件目录
target_include_directories(dispatch_queue_test
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/3rdparty
    ${CMAKE_SOURCE_DIR}/build/_deps/googletest-src/googletest/include
    ${CMAKE_SOURCE_DIR}/build/_deps/googletest-src/googlemock/include
)

message(STATUS "CMAKE_SOURCE_DIR2: ${CMAKE_SOURCE_DIR}")

# 链接GoogleTest和被测试的库
target_link_libraries(dispatch_queue_test
    PRIVATE
    dispatch_queue
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

# 添加测试
include(GoogleTest)
gtest_discover_tests(dispatch_queue_test)