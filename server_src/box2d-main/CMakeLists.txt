project(box2d)

# Define the source files for your library
FILE(GLOB box2d_src_files "include/*.h")

# Add your source files to the library
add_library(box2d STATIC ${box2d_src_files})

# Specify the directory where libbox2d.a resides
set(BOX2D_LIBRARY_DIR "/lib")

# Link against the libbox2d.a library
target_link_libraries(box2d PRIVATE ${BOX2D_LIBRARY_DIR}/libbox2d.a)
