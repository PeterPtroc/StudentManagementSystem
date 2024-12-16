cmake_minimum_required(VERSION 3.10)

# 包含根目录的 CMakeLists
project(StudentManagementSystemTests CXX)

# 包含 Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 查找所有测试源文件
file(GLOB TEST_SOURCES "*.cc")

# 创建测试可执行文件
add_executable(StudentManagementSystemTests ${TEST_SOURCES})

# 链接 Google Test 和 pthread
target_link_libraries(StudentManagementSystemTests gtest gtest_main pthread)

# 添加测试
add_test(NAME StudentManagementSystemTests COMMAND StudentManagementSystemTests)
