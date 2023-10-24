project(Worms)
FILE(GLOB server_src_files "*.cpp")
add_library(server_lib STATIC ${server_src_files})
target_link_libraries(server_lib common_lib)