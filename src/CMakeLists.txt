# 设置头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/viewmodel)
include_directories(${PROJECT_SOURCE_DIR}/include/common)
# 设置源文件目录
#aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# 设置编译文件
file(GLOB_RECURSE SRC_LIST
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/include/SDL2/*.h
        ${PROJECT_SOURCE_DIR}/include/*.hpp
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        )

# 指定生成目标
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE third_party)
# 指定安装图片资源到目录
file(COPY ${PROJECT_SOURCE_DIR}/src/view/textures DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY common/material DESTINATION ${CMAKE_BINARY_DIR}/resources)
