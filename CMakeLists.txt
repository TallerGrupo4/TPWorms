cmake_minimum_required(VERSION 3.12)

project(Worms)

add_subdirectory(client_src)
add_subdirectory(common_src)
add_subdirectory(server_src)

add_executable(client client_main.cpp)
add_executable(server server_main.cpp)

target_link_libraries(client common_lib client_lib)
target_link_libraries(server common_lib server_lib)
