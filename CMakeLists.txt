cmake_minimum_required(VERSION 3.12)

project(Worms
    VERSION 0.0.1
    DESCRIPTION "Worms game")


include(CTest)

option(TESTING "Enable testing" OFF)
if (TESTING)
    add_definitions(-DTESTING)
endif()

if(TESTING)
    message("Testing enabled")
    add_subdirectory(tests)
endif()

include(cmake/UpdateGitSubmodules.cmake)
set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory(client_src/libSDL2pp-0.16.2)
include_directories(${SDL2PP_INCLUDE_DIRS})

add_subdirectory(external)
add_subdirectory(server_src)
add_subdirectory(client_src)
add_subdirectory(common_src)

add_executable(worms_server server_main.cpp)
add_executable(worms client_main.cpp)

target_link_libraries(worms_server common_lib server_lib)
target_link_libraries(worms common_lib client_lib SDL2pp)

target_include_directories(worms PRIVATE client_src/QT)
target_include_directories(worms PRIVATE client_src)
target_include_directories(worms PRIVATE common_src)

set_target_properties(worms PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_FLAGS "-Wall -Werror -fPIC -std=c++17")



install(TARGETS worms_server worms
        RUNTIME DESTINATION /usr/bin
)

install(FILES ${CMAKE_SOURCE_DIR}/external/config/config.yaml
        DESTINATION /etc/worms
)

install(FILES ${CMAKE_SOURCE_DIR}/server_src/config.h
        DESTINATION /etc/worms
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/client_src
        DESTINATION /var/worms
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/server_src
        DESTINATION /var/worms
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/common_src
        DESTINATION /var/worms
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/tests
        DESTINATION /var/worms
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/external
        DESTINATION /var/worms
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/cmake
        DESTINATION /var/worms
)
