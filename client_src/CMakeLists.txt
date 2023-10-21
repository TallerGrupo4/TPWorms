project(Worms)

# Globbing source files in the client_src directory
FILE(GLOB client_src_files "*.cpp")
message (STATUS "Client's source files loaded: ${client_src_files}")

# Creating a library from the source files
add_library(client_lib STATIC ${client_src_files})

# Link the client executable with the common library
target_link_libraries(client_lib common_lib)
