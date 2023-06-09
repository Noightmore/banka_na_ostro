set(CMAKE_CXX_STANDARD 23)

# Define your library target
add_library(Bank STATIC
        include/data/models/UserAccount.hpp
        lib/data/models/UserAccount.cpp
        include/services/SiteFunctionality.hpp
        lib/services/BusinessLogic.cpp
        Bank.hpp
        Bank.cpp
        include/data/models/Balance.hpp
        include/data/models/Payment.hpp
        lib/data/models/Payment.cpp
        lib/data/models/BankData.cpp
        include/data/models/BankData.hpp
        lib/data/models/Balance.cpp
        include/data/models/Money.hpp
        lib/data/models/ExchangeRate.cpp
        include/data/models/ExchangeRate.hpp
        include/data/ApplicationDbContext.hpp
        lib/data/ApplicationDbContext.cpp
        include/pages/LoginPage.hpp
        lib/pages/LoginPage.cpp
        include/services/BusinessLogic.hpp
        include/services/AuthStatus.h
        include/pages/Shared/Page.hpp
        include/pages/ErrorPage.hpp
        lib/pages/ErrorPage.cpp include/pages/VerificationNoticePage.hpp lib/pages/VerificationNoticePage.cpp include/pages/UserAccountPage.hpp lib/pages/UserAccountPage.cpp)

# Add the include directories for libfcgi-dev
#include_directories(/usr/include/fastcgi)

# Set include directories
target_include_directories(Bank PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(LibXml2 REQUIRED)
# not needed if installed via the official method
#find_package(cppcms REQUIRED)

# Set link libraries
target_link_libraries(Bank PRIVATE LibXml2::LibXml2)
# Set library version and API compatibility level
set_target_properties(Bank PROPERTIES VERSION 1.0 SOVERSION 1)
