set(CMAKE_CXX_STANDARD 23)

# Define your library target
add_library(Api STATIC
        include/data/models/UserAccount.hpp
        lib/data/models/UserAccount.cpp
        include/services/SiteFunctionality.hpp
        lib/services/BusinessLogic.cpp
        Api.hpp
        Api.cpp
        include/data/models/Balance.hpp
        include/data/models/Payment.hpp
        lib/data/models/Payment.cpp
        lib/data/models/BankData.cpp
        include/data/models/BankData.hpp
        lib/data/models/Balance.cpp
        include/data/models/Money.hpp
        lib/data/models/ExchangeRate.cpp
        include/data/models/ExchangeRate.hpp include/data/ApplicationDbContext.hpp lib/data/ApplicationDbContext.cpp)

# Set include directories
target_include_directories(Api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set library version and API compatibility level
set_target_properties(Api PROPERTIES VERSION 1.0 SOVERSION 1)
