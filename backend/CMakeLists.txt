cmake_minimum_required(VERSION 3.25)
project(backend)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

# Set the output folder for the executable
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# this is for test coverage using
#--coverage -v -fprofile-arcs -ftest-coverage -fprofile-correction
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pipe -std=c++23 -g --coverage")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# test coverage
#set(CMAKE_THREAD_LIBS_INIT "-lpthread")
#set(CMAKE_HAVE_THREADS_LIBRARY 1)
#set(CMAKE_USE_WIN32_THREADS_INIT 0)
#set(CMAKE_USE_PTHREADS_INIT 1)
#set(THREADS_PREFER_PTHREAD_FLAG ON)

# Set compiler options
#add_compile_options(-O3 -pipe -std=c++23)

# enable tests
enable_testing()

## vcpkg integration (/home/rob/.clion-vcpkg/vcpkg - for gentoo)
# for ubuntu - /usr/local/share/vcpkg
#set(VCPKG_ROOT "/home/rob/.clion-vcpkg/vcpkg") # vcpkg lib folder path

if(EXISTS "/etc/os-release")
    file(STRINGS "/etc/os-release" OS_RELEASE_CONTENTS)
    foreach(line ${OS_RELEASE_CONTENTS})
        if(line MATCHES "Ubuntu") # production operating system
            set(VCPKG_ROOT "/usr/local/share/vcpkg")
        elseif(line MATCHES "Gentoo") # or any desktop operating system with vcpkg installed using clion
            # Run the `whoami` command
            execute_process(COMMAND whoami
                    OUTPUT_VARIABLE OUTPUT
                    RESULT_VARIABLE RESULT)

            string(REPLACE "\n" "" OUTPUT "${OUTPUT}")

            set(VCPKG_ROOT "/home/${OUTPUT}/.clion-vcpkg/vcpkg")
        #elseif(line MATCHES "Opensuse")
            # Do something specific for Debian
        endif()
    endforeach()
endif()


## Include vcpkg.cmake
if(EXISTS "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message(STATUS "Using vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else()
    message(FATAL_ERROR "vcpkg.cmake not found in ${VCPKG_ROOT}/scripts/buildsystems/")
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

add_executable(TestModel tests/TestModel.cpp)
target_link_libraries(TestModel PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main Api)

add_test(NAME TestModel COMMAND TestModel)
