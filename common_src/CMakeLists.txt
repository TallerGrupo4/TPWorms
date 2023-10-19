project(cmake-demo) 

add_subdirectory(socket)

target_link_libraries(demo mysocket)

FILE(GLOB common_src "*.cpp")
message (STATUS "Cargué ${common_src}")

add_library(myclasses
  ${common_src}
)
