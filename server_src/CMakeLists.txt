project(Worms)
FILE(GLOB server_src_files "*.cpp" "*.h")
FILE(GLOB game_src_files "game_src/*.cpp" "game_src/*.h")

add_subdirectory(box2d)
add_library(server_lib STATIC ${server_src_files} ${game_src_files})
target_link_libraries(server_lib box2d common_lib)
# target_include_directories(server_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/box2d/include/box2d)  # Adjust the path accordingly

