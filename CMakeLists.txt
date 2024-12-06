cmake_minimum_required(VERSION 3.10)
project(StudentManagementSystem C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 头文件目录
include_directories(include/calculate)
include_directories(include/calculate/class)
include_directories(include/calculate/total)
include_directories(include/info)
include_directories(include/utils)
include_directories(include/io)
include_directories(include/config) 


# 查找所有源文件
file(GLOB_RECURSE SOURCES "src/*.c")

# 输出可执行文件
add_executable(StudentManagementSystem ${SOURCES})