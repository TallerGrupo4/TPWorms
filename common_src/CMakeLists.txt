project(cmake-demo) 

FILE(GLOB common_src "*.cpp")
message (STATUS "Cargué ${common_src}")

add_library(myclasses
  ${common_src}
)
