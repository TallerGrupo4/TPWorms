project(Worms) 

add_subdirectory(socket)

FILE(GLOB common_src_files "*.cpp")
message (STATUS "Cargué ${common_src}")

add_library(common_lib STATIC
  ${common_src_files}
)
