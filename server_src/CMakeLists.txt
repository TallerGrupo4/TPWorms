project(Worms)

# Globbing source files in the client_src directory
FILE(GLOB server_src_files "*.cpp")

# Creating a library from the source files
add_library(server_lib STATIC ${server_src_files})

# Link the client executable with the common library
target_link_libraries(server_lib common_lib)
