cmake_minimum_required(VERSION 3.12)

project(Worms
    VERSION 0.0.1
    DESCRIPTION "Worms game")


include(CTest)

# Define the TESTING option with a default value of OFF
option(TESTING "Enable testing" OFF)
if (TESTING)
    add_definitions(-DTESTING)
endif()

if(TESTING)
    message("Testing enabled")
    add_subdirectory(tests)
endif()

include(cmake/UpdateGitSubmodules.cmake)

add_subdirectory(external)
add_subdirectory(client_src)
add_subdirectory(common_src)
add_subdirectory(server_src)

add_executable(client client_main.cpp)
add_executable(server server_main.cpp)

# find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(client common_lib client_lib)
target_link_libraries(server common_lib server_lib)

target_include_directories(client PRIVATE client_src/QT)
target_include_directories(client PRIVATE client_src)
target_include_directories(client PRIVATE common_src)
target_include_directories(server PRIVATE server_src)
target_include_directories(server PRIVATE common_src)

set_target_properties(client PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")


