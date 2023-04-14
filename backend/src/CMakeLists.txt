set(CMAKE_CXX_STANDARD 23)

# Define your library target
add_library(Api STATIC
        include/models/UserAccount.hpp
        lib/models/UserAccount.cpp
        include/services/SiteFunctionality.hpp
        lib/services/BusinessLogic.cpp
        Api.hpp
        Api.cpp
        include/models/Balance.hpp
        include/models/Payment.hpp
        lib/models/Payment.cpp
        lib/models/BankData.cpp
        include/models/BankData.hpp
        lib/models/Balance.cpp
        include/models/Money.hpp
        lib/models/ExchangeRate.cpp
        include/models/ExchangeRate.hpp)

# Set include directories
target_include_directories(Api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set library version and API compatibility level
set_target_properties(Api PROPERTIES VERSION 1.0 SOVERSION 1)
