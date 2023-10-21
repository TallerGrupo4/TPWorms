project(Worms)

FILE(GLOB common_src_files "*.cpp")
message (STATUS "Common's source files loaded: ${common_src_files}")

add_library(common_lib STATIC ${common_src_files})
