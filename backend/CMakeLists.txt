cmake_minimum_required(VERSION 3.25)
project(backend)

# Set the output folder for the executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)

add_executable(backend.cgi
        src/main.cpp
        include/models/UserAccount.hpp
        lib/models/UserAccount.cpp
        include/services/SiteFunctionality.hpp
        lib/services/BusinessLogic.cpp
        src/Api.hpp
        src/Api.cpp
        include/models/Balance.hpp include/models/Payment.hpp lib/models/Payment.cpp)
