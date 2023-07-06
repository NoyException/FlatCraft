add_subdirectory(SDL)

add_library(third_party INTERFACE)
target_link_libraries(third_party INTERFACE SDL2::SDL2)