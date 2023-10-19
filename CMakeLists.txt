cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

add_executable(demo main.cpp)
add_subdirectory(common_src)

target_link_libraries(demo myclasses)
