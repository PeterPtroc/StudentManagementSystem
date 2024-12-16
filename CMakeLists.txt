cmake_minimum_required(VERSION 3.10)
project(StudentManagementSystem C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 选择编译器
option(USE_MINGW "Use x86_64-w64-mingw32-g++" OFF)

if(USE_MINGW)
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
else()
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
endif()

# 头文件目录
include_directories(include/calculate)
include_directories(include/calculate/class)
include_directories(include/calculate/total)
include_directories(include/info)
include_directories(include/utils)
include_directories(include/io)
include_directories(include/config)
include_directories(include/icon)

# 查找所有源文件
file(GLOB_RECURSE SOURCES "src/*.c")

# 添加资源文件
if(USE_MINGW)
    set(RESOURCE_FILES src/icon/resource.rc)
endif()

# 输出可执行文件
add_executable(StudentManagementSystem ${SOURCES} ${RESOURCE_FILES})

# 设置调试和发布模式
target_compile_options(StudentManagementSystem PRIVATE
    $<$<CONFIG:DEBUG>:-g -fsanitize=address>
    $<$<CONFIG:RELEASE>:-O3>
)

# 添加ASCAN
target_link_options(StudentManagementSystem PRIVATE
    $<$<CONFIG:DEBUG>:-fsanitize=address>
)

# 链接资源文件
if(USE_MINGW)
    target_sources(StudentManagementSystem PRIVATE ${RESOURCE_FILES})
endif()


# --------------------------
# Google Test Setup
# --------------------------

# 通过 FetchContent 下载 Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0  # 或者使用最新的稳定版本
)
FetchContent_MakeAvailable(googletest)

# 设置测试目录
enable_testing()

# 创建测试文件夹
add_subdirectory(test)