
#include "Bank.hpp"
#include "include/services/SiteFunctionality.hpp"
#include "include/services/BusinessLogic.hpp"

namespace bank
{
    void Bank::startServer()
    {
        std::cout << "Starting server..." << std::endl;
        services::SiteFunctionality* site = new services::BusinessLogic();
        site->run();

    }
}