cmake_minimum_required(VERSION 3.25)
project(backend)

# Set the output folder for the executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)

add_executable(backend.cgi src/main.cpp)
