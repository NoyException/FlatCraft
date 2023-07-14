CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

project(FlatCraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(test)