#ifndef BANK_LOGINPAGE_HPP
#define BANK_LOGINPAGE_HPP

#include <string>
#include <iostream>

#include "include/pages/Shared/PageRoute.hpp"

namespace bank::pages
{
    class LoginPage
    {
        public:
                static void generateLoginPage(std::string& hostIpAddress);
    };
}


#endif //BANK_LOGINPAGE_HPP
