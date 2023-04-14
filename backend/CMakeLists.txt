cmake_minimum_required(VERSION 3.25)
project(backend)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

# Set the output folder for the executable
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# Set compiler options
add_compile_options(-O3 -pipe -std=c++23)

# enable tests
enable_testing()

## vcpkg integration (/home/rob/.clion-vcpkg/vcpkg - for gentoo)
set(VCPKG_ROOT "/usr/local/share/vcpkg") # vcpkg lib folder path
#
## Include vcpkg.cmake
if(EXISTS "/usr/local/share/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "/usr/local/share/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message(STATUS "Using vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else()
    message(FATAL_ERROR "vcpkg.cmake not found in /usr/local/share/vcpkg/scripts/buildsystems/")
endif()

#set(GTest_DIR "/usr/local/share/vcpkg/packages")
set(CMAKE_PREFIX_PATH "/usr/local/share/vcpkg/packages/gtest_x64-linux")
#
## Install packages listed in vcpkg.json
#file(READ "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json" VCPKG_JSON)
#string(JSON VCPKG_PACKAGES version-string VCPKG_JSON)
#message("Installing packages: ${VCPKG_PACKAGES}")
#include("${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
#vcpkg_install_packages(${VCPKG_PACKAGES})

# load already installed packages
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(backend.cgi main.cpp)
target_link_libraries(backend.cgi PRIVATE Api)

add_executable(Test tests/TestModel.cpp)
target_link_libraries(Test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main Api)

add_test(NAME Test COMMAND Test)
