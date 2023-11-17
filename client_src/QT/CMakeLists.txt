project(Worms)
add_definitions(-DASSETS_PATH="${PROJECT_SOURCE_DIR}/assets")
cmake_minimum_required(VERSION 3.8)
# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

#include_directories(${PROJECT_SOURCE_DIR})

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        mainwindow.ui
)

# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)
# Habilito autorcc para manejar automaticamente los QResources
set(CMAKE_AUTORCC ON)
#
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

add_library(lobby
  assets/resources.qrc
  lobby_renderer.cpp
  mainwindow.cpp
  ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(lobby Qt5::Widgets Qt5::Core)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")
