cmake_minimum_required(VERSION 3.10)
project(StudentManagementSystem C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 头文件目录
include_directories(include)

# 包含所有源码子目录
file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "include/*")
foreach(HEADER_DIR ${HEADER_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${HEADER_DIR})
        include_directories(${CMAKE_SOURCE_DIR}/${HEADER_DIR})
    endif()
endforeach()

# 查找所有源文件
file(GLOB_RECURSE SOURCES "src/*.c")

# 输出可执行文件
add_executable(StudentManagementSystem ${SOURCES})