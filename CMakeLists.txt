cmake_minimum_required(VERSION 3.24)
project(FlatCraft)

set(CMAKE_CXX_STANDARD 17)

# 设置头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
# 设置源文件目录
#aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# 设置编译文件
file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCE_DIR}/include/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)
# 指定生成目标
add_executable(FlatCraft ${SRC_LIST} include/common.h)