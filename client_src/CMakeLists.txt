project(Worms)
FILE(GLOB client_src_files "*.cpp")
add_definitions(-DEFFECTS_SPRITES_PATH="${PROJECT_SOURCE_DIR}/sprites/Effects"
-DMISC_SPRITES_PATH="${PROJECT_SOURCE_DIR}/sprites/Misc"
-DWEAPONSICONS_SPRITES_PATH="${PROJECT_SOURCE_DIR}/sprites/'Weapon Icons'"
-DWEAPONS_SPRITES_PATH="${PROJECT_SOURCE_DIR}/sprites/Weapons"
-DWORMS_SPRITES_PATH="${PROJECT_SOURCE_DIR}/sprites/Worms"
)
add_subdirectory(QT)
add_library(client_lib STATIC
${client_src_files})
target_compile_options(client_lib PRIVATE -fPIC)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")
target_include_directories(client_lib PRIVATE QT)
target_link_libraries(client_lib common_lib ${SDL2PP_LIBRARIES} lobby)
#Agrego parte de SDL2PP
#include(FindPkgConfig)
#pkg_search_module(SDL2 REQUIRED sdl2)
#pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
#include_directories("libSDL2pp-0.16.2/SDL2pp")
#include_directories(${SDL2PP_INCLUDE_DIRS})
#target_link_libraries(client_lib SDL2pp)
#Agrego parte de QT
#add_subdirectory(QT)
#target_compile_options(client_lib PRIVATE -fPIC)
#set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")
#target_include_directories(client_lib PRIVATE QT)
#target_link_libraries(client_lib lobby)
