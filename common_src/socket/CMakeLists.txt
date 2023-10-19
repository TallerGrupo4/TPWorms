project(cmake-demo) 

FILE(GLOB socket "*.cpp")
message (STATUS "Cargué ${socket}")

add_library(mysocket
  ${socket}
)

