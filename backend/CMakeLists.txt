cmake_minimum_required(VERSION 3.25)
project(backend)

# Set the output folder for the executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# vcpkg integration (/home/rob/.clion-vcpkg/vcpkg - for gentoo)
#set(VCPKG_ROOT "/usr/local/share/vcpkg") # vcpkg lib folder path
#
## Include vcpkg.cmake
#if(EXISTS "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
#    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
#    message(STATUS "Using vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
#else()
#    message(FATAL_ERROR "vcpkg.cmake not found in ${VCPKG_ROOT}/scripts/buildsystems/")
#endif()

# Install packages listed in vcpkg.json
#file(READ "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json" VCPKG_JSON)
#string(JSON VCPKG_PACKAGES version-string VCPKG_JSON)
#message("Installing packages: ${VCPKG_PACKAGES}")
#include("${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
#vcpkg_install_packages(${VCPKG_PACKAGES})

#find_package(boost-datetime REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(backend.cgi
        src/main.cpp
        include/models/UserAccount.hpp
        lib/models/UserAccount.cpp
        include/services/SiteFunctionality.hpp
        lib/services/BusinessLogic.cpp
        src/Api.hpp
        src/Api.cpp
        include/models/Balance.hpp
        include/models/Payment.hpp
        lib/models/Payment.cpp)
