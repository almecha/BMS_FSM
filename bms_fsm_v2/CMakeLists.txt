# Example CMake command line to create project build files:
#
# *** Windows ***
# cmake -G "Visual Studio 17 2022" -A Win32 -B Build -S .
#
# *** Linux ***
# cmake -G "Unix Makefiles" -B Build -S .

# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language (C or C++)
project(C_StateMachine VERSION 1.0 LANGUAGES C CXX)

# Collect all source files in the current directory and subdirectories, excluding CMakeFiles
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/.*")

# Include the directory containing additional header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Debugging: Print the list of source files
message("SOURCES: ${SOURCES}")

# Add an executable target
add_executable(C_StateMachineApp ${SOURCES})

# Exclude the compiler identification files
set_source_files_properties(
    ${CMAKE_BINARY_DIR}/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.c
    ${CMAKE_BINARY_DIR}/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.cpp
    PROPERTIES HEADER_FILE_ONLY TRUE
)



